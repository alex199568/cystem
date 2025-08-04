#include "point.hpp"

Point operator+(Point p, Vector v) {
    return Point{p.x + v.x, p.y + v.y, p.z + v.z};
}

Point operator-(Point p, Vector v) {
    return Point{p.x - v.x, p.y - v.y, p.z - v.z};
}

Vector operator-(Point a, Point b) {
    return Vector{a.x - b.x, a.y - b.y, a.z - b.z};
}