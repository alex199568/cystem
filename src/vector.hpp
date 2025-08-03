#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <stdio.h>
#include <math.h>

struct Vector {
    double x;
    double y;
    double z;

    void print() {
        printf("Vector(%f %f %f)\n", x, y, z);
    }
};

Vector operator+(Vector a, Vector b) {
    return Vector{a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector operator-(Vector a, Vector b) {
    return Vector{a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector operator-(Vector v) {
    return Vector{-(v.x), -(v.y), -(v.z)};
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

double squaredLength(Vector v) {
    return dot(v, v);
}

double length(Vector v) {
    return sqrt(squaredLength(v));
}

Vector unit(Vector v) {
    return v / length(v);
}

Vector cross(Vector a, Vector b) {
    return Vector{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}

#endif
