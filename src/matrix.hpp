#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <cmath>
#include <stdio.h>

#include <array>

#include "vector.hpp"
#include "point.hpp"
#include "ray.hpp"

class Matrix2 {
    std::array<double, 4> items;

    int index(int i, int j) {
        return i * 2 + j;
    }

  public:
    Matrix2() {}

    Matrix2(std::array<double, 4> values) : items(values) {}

    double get(int i, int j) {
        return items[index(i, j)];
    }

    void set(int i, int j, double d) {
        items[index(i, j)] = d;
    }

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

    Matrix2 submatrix(int iExclude, int jExclude) {
        Matrix2 result;

        int iOffset = 0;
        for (int i = 0; i < 3; ++i) {
            if (i == iExclude) {
                iOffset = 1;
                continue;
            }

            int jOffset = 0;
            for (int j = 0; j < 3; ++j) {
                if (j == jExclude) {
                    jOffset = 1;
                    continue;
                }

                result.set(i - iOffset, j - jOffset, get(i, j));
            }
        }

        return result;
    }

  public:
    Matrix3() {}

    Matrix3(std::array<double, 9> values) : items(values) {}

    double get(int i, int j) {
        return items[index(i, j)];
    }

    void set(int i, int j, double d) {
        items[index(i, j)] = d;
    }

    void print() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                printf("%6.3f ", get(i, j));
            }
            printf("\n");
        }
    }

    double minor(int i, int j) {
        return submatrix(i, j).det();
    }

    double cofactor(int i, int j) {
        double m = minor(i, j);
        if ((i + j) % 2 == 0)
            return m;
        return -m;
    }

    double det() {
        return get(0, 0) * cofactor(0, 0) +
               get(0, 1) * cofactor(0, 1) +
               get(0, 2) * cofactor(0, 2);
    }
};

class Matrix {

    std::array<double, 16> items;

    int index(int i, int j) {
        return i * 4 + j;
    }

    Matrix3 submatrix(int iExclude, int jExclude) {
        Matrix3 result;

        int iOffset = 0;
        for (int i = 0; i < 4; ++i) {
            if (i == iExclude) {
                iOffset = 1;
                continue;
            }

            int jOffset = 0;
            for (int j = 0; j < 4; ++j) {
                if (j == jExclude) {
                    jOffset = 1;
                    continue;
                }

                result.set(i - iOffset, j - jOffset, get(i, j));
            }
        }

        return result;
    }

    double minor(int i, int j) {
        return submatrix(i, j).det();
    }

    double cofactor(int i, int j) {
        double m = minor(i, j);
        if ((i + j) % 2 == 0)
            return m;
        return -m;
    }

    double det() {
        return get(0, 0) * cofactor(0, 0) +
               get(0, 1) * cofactor(0, 1) +
               get(0, 2) * cofactor(0, 2) +
               get(0, 3) * cofactor(0, 3);
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

    Matrix inverse() {
        Matrix result;

        double d = det();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                double r = cofactor(i, j) / d;
                result.set(j, i, r);
            }
        }

        return result;
    }

    Matrix transpose() {
        Matrix result;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.set(j, i, get(i, j));
            }
        }

        return result;
    }
};

Matrix operator*(Matrix a, Matrix b);

Vector operator*(Matrix m, Vector v);

Point operator*(Matrix m, Point p);

Ray operator*(Matrix m, Ray ray);

extern Matrix identity;

Matrix translation(double x, double y, double z);

Matrix rotationX(double rads);

Matrix rotationY(double rads);

Matrix rotationZ(double rads);

Matrix scale(double x, double y, double z);

Matrix lookAt(Point from, Point to, Vector up);

#endif
