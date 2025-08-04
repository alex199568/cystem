#include "image.hpp"

#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void Image::save(const char *path) {
    uint8_t *data = new uint8_t[w * h * 3];
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int i = y * w + x;
            data[i * 3 + 0] = (uint8_t)(fmin(fmax(colors[i].r * 255.0, 0.0), 255.0));
            data[i * 3 + 1] = (uint8_t)(fmin(fmax(colors[i].g * 255.0, 0.0), 255.0));
            data[i * 3 + 2] = (uint8_t)(fmin(fmax(colors[i].b * 255.0, 0.0), 255.0));
        }
    }

    stbi_write_png(path, w, h, 3, data, w * 3);

    delete[] data;
}
