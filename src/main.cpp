#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>

#include "vector.hpp"
#include "point.hpp"
#include "color.hpp"
#include "image.hpp"
#include "matrix.hpp"
#include "utils.hpp"
#include "ray.hpp"

struct Material {
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
};

struct Sphere {
    Matrix inv;
    Matrix invTr;
    Material material;
};

Sphere sphere(Matrix transform, Material material) {
    auto inv = transform.inverse();
    auto invTr = inv.transpose();
    return Sphere{inv, invTr, material};
}

struct Intersection {
    Sphere *shape;
    double t;
};

std::vector<Intersection> localIntersect(Sphere *shape, Ray ray) {
    auto sphereToRay = ray.origin - Point{0, 0, 0};
    auto a = dot(ray.direction, ray.direction);
    auto b = 2 * dot(ray.direction, sphereToRay);
    auto c = dot(sphereToRay, sphereToRay) - 1;
    auto d = b * b - 4 * a * c;

    std::vector<Intersection> result;

    if (d < 0) {
        return result;
    }

    auto sd = sqrt(d);
    auto t1 = (-b - sd) / (a * 2);
    auto t2 = (-b + sd) / (a * 2);

    Intersection i1{shape, t1};
    Intersection i2{shape, t2};

    result.push_back(i1);
    result.push_back(i2);

    return result;
}

std::vector<Intersection> intersect(Sphere *shape, Ray ray) {
    auto localRay = shape->inv * ray;
    return localIntersect(shape, localRay);
}

Vector localNormal(Point point) {
    return point - Point{0, 0, 0};
}

Vector normal(Sphere shape, Point point) {
    auto objectPoint = shape.inv * point;
    auto objectNormal = localNormal(objectPoint);
    auto worldNormal = shape.invTr * objectNormal;
    return worldNormal.unit();
}

struct Light {
    Point position;
    Color intensity;
};

Color lightning(Light light, Material material, Point point, Vector eye, Vector n) {
    auto effectiveColor = material.color * light.intensity;
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

    Point rayOrigin{0, 0, -5};
    double wallZ = 10;
    double wallSize = 7;
    int pixels = 1536;
    double pixelSize = wallSize / pixels;
    double half = wallSize / 2;
    Image canvas{pixels, pixels};

    Material material{red, 0.1, 0.9, 0.9, 200};

    Sphere shape = sphere(identity, material);

    Light light = {Point{-10, 10, -10}, gray};

    clock_t start = clock();

    for (int y = 0; y < pixels; ++y) {
        double worldY = half - pixelSize * y;
        for (int x = 0; x < pixels; ++x) {
            double worldX = -half + pixelSize * x;
            Point position{worldX, worldY, wallZ};
            Ray ray{rayOrigin, (position - rayOrigin).unit()};
            std::vector<Intersection> intersections = intersect(&shape, ray);
            if (intersections.size() > 0) {
                Intersection i1 = intersections[0];
                Intersection i2 = intersections[1];
                Intersection closest;
                if (i1.t >= 0 && i1.t < i2.t) {
                    closest = i1;
                } else if (i2.t >= 0 && i2.t < i1.t) {
                    closest = i2;
                }

                if (closest.shape) {

                    auto point = ray.at(closest.t);
                    auto n = normal(*closest.shape, point);
                    auto eye = -ray.direction;
                    auto color = lightning(light, material, point, eye, n);

                    canvas.set(x, y, color);
                }
            }
        }
    }

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Rendering time: %.6f seconds\n", duration);

    canvas.save("../../renders/light.png");

    return 0;
}
