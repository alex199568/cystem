#include <stdio.h>

struct Vector {
    double x;
    double y;
    double z;
};

void print_vector(Vector vector) {
    printf("Vector(%f %f %f)\n", vector.x, vector.y, vector.z);
}

Vector operator+(Vector a, Vector b) {
    return Vector{a.x + b.x, a.y + b.y, a.z + b.z};
}

int main() {
    printf("Cystem\n");

    Vector a = {1, 2, 3};
    print_vector(a);
    Vector b = {2, 3, 4};
    print_vector(b);
    Vector sum = a + b;
    print_vector(sum);

    return 0;
}
