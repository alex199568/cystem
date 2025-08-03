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

Point operator+(Point p, Vector v) {
    return Point{p.x + v.x, p.y + v.y, p.z + v.z};
}

Point operator-(Point p, Vector v) {
    return Point{p.x - v.x, p.y - v.y, p.z - v.z};
}

Vector operator-(Point a, Point b) {
    return Vector{a.x - b.x, a.y - b.y, a.z - b.z};
}

#endif
