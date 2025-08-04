#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "point.hpp"
#include "vector.hpp"

struct Ray {
    Point origin;
    Vector direction;

    Point at(double t) {
        return origin + direction * t;
    }
};

#endif
