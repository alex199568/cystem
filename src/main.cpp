#include <stdio.h>

#include "vector.hpp"
#include "point.hpp"

int main() {
    printf("Cystem\n");

    Vector a = {1, 2, 3};
    print(a);
    Vector b = {2, 3, 4};
    print(b);

    Point p = {-1, 3, 2};
    print(p);

    return 0;
}
