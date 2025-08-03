#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <stdio.h>

struct Color {
    double r;
    double g;
    double b;
};

void print(Color c);

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
extern Color green;
extern Color blue;

extern Color magenta;
extern Color yellow;
extern Color cyan;

#endif
