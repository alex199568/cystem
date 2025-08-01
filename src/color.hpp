#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <stdio.h>

struct Color {
    double r;
    double g;
    double b;
};

void print(Color c) {
    printf("Color(%f, %f, %f)\n", c.r, c.g, c.b);
}

Color operator+(Color a, Color b) {
    return Color{a.r + b.r, a.g + b.g, a.b + b.b};
}

Color operator-(Color a, Color b) {
    return Color{a.r - b.r, a.g - b.b, a.b - b.b};
}

Color operator*(Color a, Color b) {
    return Color{a.r * b.r, a.g * b.g, a.b * b.b};
}

Color operator*(Color a, double d) {
    return Color{a.r * d, a.g * d, a.b * d};
}

Color operator/(Color a, double d) {
    return Color{a.r / d, a.g / d, a.b / d};
}

Color white = {1, 1, 1};
Color lightGray = {0.75, 0.75, 0.75};
Color gray = {0.5, 0.5, 0.5};
Color darkGray = {0.25, 0.25, 0.25};
Color black = {0, 0, 0};

Color red = {1, 0, 0};
Color green = {0, 1, 0};
Color blue = {0, 0, 1};

Color magenta = {1, 0, 1};
Color yellow = {1, 1, 0};
Color cyan = {0, 1, 1};

#endif
