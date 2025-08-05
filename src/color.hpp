#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <stdio.h>

struct Color {
    double r;
    double g;
    double b;

    Color &operator+=(const Color &rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }
};

Color operator+(Color a, Color b);

Color operator-(Color a, Color b);

Color operator*(Color a, Color b);

Color operator*(Color a, double d);

Color operator/(Color a, double d);

extern Color white;
extern Color lightGray;
extern Color gray;
extern Color darkGray;
extern Color black;

extern Color red;
extern Color darkRed;
extern Color green;
extern Color darkGreen;
extern Color blue;
extern Color darkBlue;

extern Color magenta;
extern Color darkMagenta;
extern Color yellow;
extern Color darkYellow;
extern Color cyan;
extern Color darkCyan;

#endif
