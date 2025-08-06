#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <cmath>
#include <stdio.h>
#include <math.h>

struct Vector;

double length(Vector v);
double squaredLength(Vector v);

Vector operator-(Vector a, Vector b);
Vector operator/(Vector a, double d);
Vector operator*(Vector a, double d);
double dot(Vector a, Vector b);

struct Vector {
    double x;
    double y;
    double z;

    void print() {
        printf("Vector(%f %f %f)\n", x, y, z);
    }

    double length() {
        return sqrt(squaredLength(*this));
    }

    Vector unit() {
        return *this / length();
    }

    Vector reflect(Vector normal) {
        return *this - normal * 2 * dot(*this, normal);
    }
};

Vector operator+(Vector a, Vector b);

Vector operator-(Vector v);

Vector operator/(Vector a, double d);


Vector cross(Vector a, Vector b);

#endif
