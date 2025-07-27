#include <stdio.h>

struct Vector {
    double x;
    double y;
    double z;
};

void print(Vector vector) {
    printf("Vector(%f %f %f)\n", vector.x, vector.y, vector.z);
}

Vector operator+(Vector a, Vector b) {
    return Vector{a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector operator-(Vector a, Vector b) {
    return Vector{a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector operator*(Vector a, double d) {
    return Vector{a.x * d, a.y * d, a.z * d};
}

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

    return 0;
}
