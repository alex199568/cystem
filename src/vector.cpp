#include "vector.hpp"

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

Vector cross(Vector a, Vector b) {
    return Vector{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x};
}