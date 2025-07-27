#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

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

Vector operator/(Vector a, double d) {
    return Vector{a.x / d, a.y / d, a.z / d};
}

double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

#endif
