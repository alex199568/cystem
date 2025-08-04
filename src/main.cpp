#include <stdio.h>
#include <math.h>
#include <time.h>

#include "vector.hpp"
#include "point.hpp"
#include "color.hpp"
#include "image.hpp"
#include "matrix.hpp"
#include "utils.hpp"
#include "ray.hpp"

struct Sphere {
    Matrix inv;
};

Sphere sphere(Matrix transform) {
    return Sphere{
        transform.inverse()};
}

struct Intersection {
    Sphere *shape;
    double t;
};

bool localIntersect(Ray ray) {
    auto sphereToRay = ray.origin - Point{0, 0, 0};
    auto a = dot(ray.direction, ray.direction);
    auto b = 2 * dot(ray.direction, sphereToRay);
    auto c = dot(sphereToRay, sphereToRay) - 1;
    auto d = b * b - 4 * a * c;

    if (d < 0) {
        // will be empty intersections
        return false;
    }

    auto sd = sqrt(d);
    auto t1 = (-b - sd) / (a * 2);
    auto t2 = (-b + sd) / (a * 2);

    // return true for now, will be intersections
    return true;
}

bool intersect(Sphere shape, Ray ray) {
    auto localRay = shape.inv * ray;
    return localIntersect(localRay);
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
    Color color = red;
    Sphere shape = sphere(identity);

    clock_t start = clock();


    for (int y = 0; y < pixels; ++y) {
        double worldY = half - pixelSize * y;
        for (int x = 0; x < pixels; ++x) {
            double worldX = -half + pixelSize * x;
            Point position{worldX, worldY, wallZ};
            Ray ray{rayOrigin, (position - rayOrigin).unit()};
            if (intersect(shape, ray)) {
                canvas.set(x, y, color);
            }
        }
    }

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Rendering time: %.6f seconds\n", duration);

    canvas.save("../../renders/sphere.png");

    return 0;
}
