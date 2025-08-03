#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <stdio.h>

#include <array>

typedef std::array<double, 4> matrix2;
typedef std::array<double, 9> matrix3;
typedef std::array<double, 16> matrix;

int index2(int i, int j) {
    return i * 2 + j;
}

int index3(int i, int j) {
    return i * 3 + j;
}

int index(int i, int j) {
    return i * 4 + j;
}

void print(matrix items) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f ", items[index(i, j)]);
        }
        printf("\n");
    }
}

matrix operator*(matrix a, matrix b) {
    matrix result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double s = 0;
            for (int k = 0; k < 4; ++k) {
                s += a[index(i, k)] * b[index(k, j)];
            }
            result[index(i, j)] = s;
        }
    }

    return result;
}

matrix translation(double x, double y, double z) {
    return {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1};
}

matrix scale(double x, double y, double z) {
    return {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1};
}

#endif
