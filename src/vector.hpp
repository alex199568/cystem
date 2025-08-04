#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <stdio.h>
#include <math.h>

struct Vector;

double length(Vector v);

Vector operator/(Vector a, double d);

struct Vector {
    double x;
    double y;
    double z;

    void print() {
        printf("Vector(%f %f %f)\n", x, y, z);
    }

    Vector unit() {
        return *this / length(*this);
    }
};

Vector operator+(Vector a, Vector b);

Vector operator-(Vector a, Vector b);

Vector operator-(Vector v);

Vector operator*(Vector a, double d);

Vector operator/(Vector a, double d);

double dot(Vector a, Vector b);

double squaredLength(Vector v);

Vector cross(Vector a, Vector b);

#endif
