#include <stdio.h>

#include "vector.hpp"

int main() {
    printf("Cystem\n");

    Vector a = {1, 2, 3};
    print(a);
    Vector b = {2, 3, 4};
    print(b);
    auto sum = a + b;
    print(sum);
    auto dif = a - b;
    print(dif);
    auto m = a * 2;
    print(m);
    auto d = a / 2;
    print(d);

    auto adb = dot(a, b);
    printf("a dot b = %f\n", adb);

    auto cr = cross(a, b);
    print(cr);

    print(-a);

    return 0;
}
