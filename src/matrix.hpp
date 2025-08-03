#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <stdio.h>

#include <array>

#include "vector.hpp"
#include "point.hpp"

class Matrix2 {
    std::array<double, 4> items;

    int index(int i, int j) {
        return i * 2 + j;
    }

    double get(int i, int j) {
        return items[index(i, j)];
    }

    void set(int i, int j, double d) {
        items[index(i, j)] = d;
    }

  public:
    Matrix2() {}

    Matrix2(std::array<double, 4> values) : items(values) {}

    void print() {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                printf("%6.3f ", get(i, j));
            }
            printf("\n");
        }
    }

    double det() {
        return get(0, 0) * get(1, 1) - get(0, 1) * get(1, 0);
    }
};

class Matrix3 {

    std::array<double, 9> items;

    int index(int i, int j) {
        return i * 3 + j;
    }

    double get(int i, int j) {
        return items[index(i, j)];
    }

    void set(int i, int j, double d) {
        items[index(i, j)] = d;
    }

  public:
    Matrix3() {}

    Matrix3(std::array<double, 9> values) : items(values) {}

    void print() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                printf("%6.3f ", get(i, j));
            }
            printf("\n");
        }
    }
};

class Matrix {

    std::array<double, 16> items;

    int index(int i, int j) {
        return i * 4 + j;
    }

  public:
    Matrix() {}

    Matrix(std::array<double, 16> values) : items(values) {}

    double get(int i, int j) {
        return items[index(i, j)];
    }

    void set(int i, int j, double d) {
        items[index(i, j)] = d;
    }

    void print() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                printf("%6.3f ", get(i, j));
            }
            printf("\n");
        }
    }
};

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

Matrix translation(double x, double y, double z) {
    return Matrix({1, 0, 0, x,
                   0, 1, 0, y,
                   0, 0, 1, z,
                   0, 0, 0, 1});
}

Matrix scale(double x, double y, double z) {
    return Matrix({x, 0, 0, 0,
                   0, y, 0, 0,
                   0, 0, z, 0,
                   0, 0, 0, 1});
}

#endif
