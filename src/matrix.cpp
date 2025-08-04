#include "matrix.hpp"

Matrix operator*(Matrix a, Matrix b) {
    Matrix result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double s = 0;
            for (int k = 0; k < 4; ++k) {
                s += a.get(i, k) * b.get(k, j);
            }
            result.set(i, j, s);
        }
    }

    return result;
}

Vector operator*(Matrix m, Vector v) {
    return Vector{
        m.get(0, 0) * v.x + m.get(0, 1) * v.y + m.get(0, 2) * v.z,
        m.get(1, 0) * v.x + m.get(1, 1) * v.y + m.get(1, 2) * v.z,
        m.get(2, 0) * v.x + m.get(2, 1) * v.y + m.get(2, 2) * v.z,
    };
}

Point operator*(Matrix m, Point p) {
    return Point{
        m.get(0, 0) * p.x + m.get(0, 1) * p.y + m.get(0, 2) * p.z + m.get(0, 3),
        m.get(1, 0) * p.x + m.get(1, 1) * p.y + m.get(1, 2) * p.z + m.get(1, 3),
        m.get(2, 0) * p.x + m.get(2, 1) * p.y + m.get(2, 2) * p.z + m.get(2, 3)};
}

Ray operator*(Matrix m, Ray ray) {
    return Ray{
        m * ray.origin,
        m * ray.direction};
}

Matrix identity({1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1});

Matrix translation(double x, double y, double z) {
    return Matrix({1, 0, 0, x,
                   0, 1, 0, y,
                   0, 0, 1, z,
                   0, 0, 0, 1});
}

Matrix rotationX(double rads) {
    double c = cos(rads);
    double s = sin(rads);
    return Matrix({1, 0, 0, 0,
                   0, c, -s, 0,
                   0, s, c, 0,
                   0, 0, 0, 1});
}

Matrix rotationY(double rads) {
    double c = cos(rads);
    double s = sin(rads);
    return Matrix({c, 0, s, 0,
                   0, 1, 0, 0,
                   -s, 0, c, 0,
                   0, 0, 0, 1});
}

Matrix rotationZ(double rads) {
    double c = cos(rads);
    double s = sin(rads);
    return Matrix({c, -s, 0, 0,
                   s, c, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1});
}

Matrix scale(double x, double y, double z) {
    return Matrix({x, 0, 0, 0,
                   0, y, 0, 0,
                   0, 0, z, 0,
                   0, 0, 0, 1});
}
