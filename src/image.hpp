#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include "color.hpp"

struct Image {
    int w;
    int h;
    Color *colors;

    Image(int w, int h) : w(w), h(h) {
        colors = new Color[w * h];
    }

    ~Image() {
        delete[] colors;
    }

    int index(int x, int y) {
        return y * w + x;
    }

    Color get(int x, int y) {
        return colors[index(x, y)];
    }

    void set(int x, int y, Color color) {
        colors[index(x, y)] = color;
    }

    void save(const char *path);
};

#endif
