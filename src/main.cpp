#include <stdio.h>

#include "vector.hpp"
#include "point.hpp"

int main() {
    printf("Cystem\n");

    Vector a = {1, 2, 3};
    print(a);
    Vector b = {2, 3, 4};
    print(b);

    Point p1 = {-1, 3, 2};
    print(p1);
    Point p2 = {2, -8, 3};
    print(p2);

    auto r1 = p1 + a;
    print(r1);
    auto r2 = p1 - b;
    print(r2);
    auto r3 = p1 - p2;
    print(r3);

    return 0;
}
