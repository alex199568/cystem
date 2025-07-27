#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <stdio.h>

struct Point {
    double x;
    double y;
    double z;
};

void print(Point p) {
    printf("Point(%f, %f, %f)\n", p.x, p.y, p.z);
}

#endif
