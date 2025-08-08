#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <algorithm>

#include "vector.hpp"
#include "point.hpp"
#include "color.hpp"
#include "image.hpp"
#include "matrix.hpp"
#include "utils.hpp"
#include "ray.hpp"

enum PatternType {
    STRIPES,
    GRADIENT,
    RING
};

struct Pattern;

struct Material {
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    Pattern *pattern;
};

enum ShapeType {
    SPHERE,
    PLANE
};

struct Shape {
    Matrix inv;
    Matrix invTr;
    Material material;
    ShapeType type;
};

struct Light {
    Point position;
    Color intensity;
};

struct Camera {
    int w;
    int h;
    double pixelSize;
    double halfWidth;
    double halfHeight;
    Matrix inv;
    Point origin;

    Ray rayForPixel(int x, int y) {
        auto xOffset = (x + 0.5) * pixelSize;
        auto yOffset = (y + 0.5) * pixelSize;
        auto worldX = halfWidth - xOffset;
        auto worldY = halfHeight - yOffset;
        auto pixel = inv * Point{worldX, worldY, -1};
        auto direction = (pixel - origin).unit();
        return Ray{origin, direction};
    }
};

Camera camera(int w, int h, double fov, Matrix view) {
    auto halfView = tan(fov / 2);
    auto aspect = (double)w / (double)h;
    double halfWidth = 0.0;
    double halfHeight = 0.0;
    if (aspect >= 1) {
        halfWidth = halfView;
        halfHeight = halfView / aspect;
    } else {
        halfWidth = halfView * aspect;
        halfHeight = halfView;
    }
    auto pixelSize = halfWidth * 2 / (double)w;
    auto inv = view.inverse();
    auto origin = inv * Point{0, 0, 0};
    return Camera{
        w, h,
        pixelSize, halfWidth, halfHeight,
        inv, origin};
}

Shape sphere(Matrix transform, Material material) {
    auto inv = transform.inverse();
    auto invTr = inv.transpose();
    return Shape{inv, invTr, material, SPHERE};
}

Shape plane(Matrix transform, Material material) {
    auto inv = transform.inverse();
    auto invTr = inv.transpose();
    return Shape{inv, invTr, material, PLANE};
}

struct Intersection {
    Shape *shape;
    double t;
};

bool compareIntersections(Intersection i1, Intersection i2) {
    return i1.t < i2.t;
}

struct Pattern {
    Color a;
    Color b;
    Matrix inv;
    PatternType type;

    Color stripe(Point point) {
        auto x = std::floor(point.x);
        if (((int)x) % 2 == 0)
            return a;
        return b;
    }

    Color gradient(Point point) {
        auto distance = b - a;
        auto fraction = point.x - std::floor(point.x);
        return a + distance * fraction;
    }

    Color ring(Point point) {
        auto xz = std::floor(sqrt(point.x * point.x + point.z * point.z));
        if ((int)xz % 2 == 0)
            return a;
        return b;
    }

    Color at(Shape *shape, Point point) {
        auto objectPoint = shape->inv * point;
        auto patternPoint = inv * objectPoint;
        if (type == STRIPES)
            return stripe(patternPoint);
        if (type == GRADIENT)
            return gradient(patternPoint);
        if (type == RING)
            return ring(patternPoint);
        return black;
    }
};

Pattern stripes(Color a, Color b, Matrix tr) {
    return Pattern{a, b, tr.inverse(), STRIPES};
}

Pattern gradient(Color a, Color b, Matrix tr) {
    return Pattern{a, b, tr.inverse(), GRADIENT};
}

Pattern ring(Color a, Color b, Matrix tr) {
    return Pattern{a, b, tr.inverse(), RING};
}

std::vector<Intersection> intersectionsBuffer;
std::vector<Shape> shapes;
std::vector<Light> lights;

Intersection hit() {
    Intersection result{nullptr, 0.0};
    for (auto &intersection : intersectionsBuffer) {
        if (intersection.t >= 0.0)
            return intersection;
    }
    return result;
}

void intersectSphere(Shape *shape, Ray ray) {
    auto sphereToRay = ray.origin - Point{0, 0, 0};
    auto a = dot(ray.direction, ray.direction);
    auto b = 2 * dot(ray.direction, sphereToRay);
    auto c = dot(sphereToRay, sphereToRay) - 1;
    auto d = b * b - 4 * a * c;

    if (d < 0) {
        return;
    }

    auto sd = sqrt(d);
    auto t1 = (-b - sd) / (a * 2);
    auto t2 = (-b + sd) / (a * 2);

    Intersection i1{shape, t1};
    Intersection i2{shape, t2};

    intersectionsBuffer.push_back(i1);
    intersectionsBuffer.push_back(i2);
}

void intersectPlane(Shape *shape, Ray ray) {
    if (abs(ray.direction.y) < epsilon) {
        return;
    }

    auto t = -ray.origin.y / ray.direction.y;
    Intersection i{shape, t};
    intersectionsBuffer.push_back(i);
}

void intersect(Shape *shape, Ray ray) {
    auto localRay = shape->inv * ray;

    if (shape->type == SPHERE)
        intersectSphere(shape, localRay);
    else if (shape->type == PLANE)
        intersectPlane(shape, localRay);
}

void intersect(Ray ray) {
    intersectionsBuffer.clear();
    for (auto &shape : shapes) {
        intersect(&shape, ray);
    }
    std::sort(intersectionsBuffer.begin(), intersectionsBuffer.end(), compareIntersections);
}

Vector sphereNormal(Point point) {
    return point - Point{0, 0, 0};
}

Vector planeNormal(Point point) {
    return Vector{0, 1, 0};
}

Vector normal(Shape shape, Point point) {
    auto objectPoint = shape.inv * point;
    Vector objectNormal;
    if (shape.type == SPHERE) {
        objectNormal = sphereNormal(objectPoint);
    } else if (shape.type == PLANE) {
        objectNormal = planeNormal(objectPoint);
    }
    auto worldNormal = shape.invTr * objectNormal;
    return worldNormal.unit();
}

struct IntersectionContext {
    Intersection h;
    Point point;
    Vector eye;
    Vector n;
    Point overPoint;
};

IntersectionContext context(Intersection i, Ray ray) {
    auto point = ray.at(i.t);
    auto eye = -ray.direction;
    auto n = normal(*i.shape, point);
    Vector adjustedNormal = n;
    if (dot(n, eye) < 0) {
        adjustedNormal = -n;
    }
    auto overPoint = point + adjustedNormal * epsilon;
    return IntersectionContext{i, point, eye, n, overPoint};
}

Color lightning(Light light, double shadowValue, IntersectionContext intersectionContext) {
    auto material = intersectionContext.h.shape->material;

    auto materialColor = material.color;
    if (material.pattern) {
        materialColor = material.pattern->at(intersectionContext.h.shape, intersectionContext.point);
    }

    auto point = intersectionContext.point;
    auto eye = intersectionContext.eye;
    auto n = intersectionContext.n;

    auto effectiveColor = materialColor * light.intensity * (1.0 - shadowValue);
    auto lightV = (light.position - point).unit();
    auto ambient = effectiveColor * material.ambient;
    auto lightDotNormal = dot(lightV, n);
    if (lightDotNormal < 0) {
        return ambient;
    }
    auto diffuse = effectiveColor * (material.diffuse * lightDotNormal);
    auto reflect = (-lightV).reflect(n);
    auto reflectDotEye = dot(reflect, eye);
    if (reflectDotEye <= 0)
        return ambient + diffuse;
    auto factor = pow(reflectDotEye, material.shininess);
    auto specular = light.intensity * (material.specular * factor);
    return ambient + diffuse + specular;
}

double shadow(Light light, Point point) {
    auto v = light.position - point;
    auto distance = v.length();
    auto direction = v.unit();
    Ray ray{point, direction};
    intersect(ray);
    Intersection h = hit();
    if (h.shape) {
        if (h.t < distance)
            return 1.0;
        return 0.0;
    }
    return 0.0;
}

void render() {
    Image image(128, 96);

    for (int y = 10; y < 30; ++y) {
        for (int x = 20; x < 80; ++x) {
            image.set(x, y, red);
        }
    }

    image.save("../../renders/image.png");
}

int main() {
    printf("Cystem\n");

    Material redMaterial{red, 0.1, 0.9, 0.9, 200};
    Material greenMaterial{green, 0.1, 0.9, 0.9, 200};
    Material grayMaterial{gray, 0.1, 0.9, 0.9, 200};

    Pattern pattern = ring(lightGray, darkGray, scale(0.1, 0.1, 0.1));
    Material patternMaterial{black, 0.1, 0.9, 0.9, 200, &pattern};

    Shape sphere1 = sphere(translation(-0.5, 0.5, 0) * scale(0.5, 0.5, 0.5), redMaterial);
    shapes.push_back(sphere1);
    Shape sphere2 = sphere(translation(0.5, 0.2, 0) * scale(0.5, 0.5, 0.5), greenMaterial);
    shapes.push_back(sphere2);
    Shape floor = plane(scale(10, 0.1, 10), patternMaterial);
    shapes.push_back(floor);

    Light light1 = {Point{-10, 10, -10}, gray};
    lights.push_back(light1);
    Light light2 = {Point{10, 10, -10}, darkGray};
    lights.push_back(light2);

    clock_t start = clock();

    auto cam = camera(1920, 1080, pi / 3, lookAt(Point{0, 1, -4}, Point{0, 0, 0}, Vector{0, 1, 0}));
    Image canvas{cam.w, cam.h};

    for (int y = 0; y < cam.h; ++y) {
        for (int x = 0; x < cam.w; ++x) {
            auto ray = cam.rayForPixel(x, y);

            intersect(ray);

            Intersection h = hit();
            if (h.shape) {
                auto color = Color{0, 0, 0};
                for (auto &light : lights) {
                    auto ctx = context(h, ray);
                    auto s = shadow(light, ctx.overPoint);
                    color += lightning(light, s, ctx);
                }

                canvas.set(x, y, color);
            }
        }
    }

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Rendering time: %.6f seconds\n", duration);

    canvas.save("../../renders/patterns.png");

    return 0;
}
