#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <stdio.h>

#include "vector.hpp"

struct Point {
    double x;
    double y;
    double z;

    void print() {
        printf("Point(%f, %f, %f)\n", x, y, z);
    }
};

Point operator+(Point p, Vector v);

Point operator-(Point p, Vector v);

Vector operator-(Point a, Point b);

#endif
