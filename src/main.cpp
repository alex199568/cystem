#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "vector.hpp"
#include "point.hpp"
#include "color.hpp"
#include "image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    printf("Cystem\n");

    Image image(128, 96);

    for (int y = 10; y < 30; ++y) {
        for (int x = 20; x < 80; ++x) {
            image.set(x, y, red);
        }
    }

    uint8_t *data = new uint8_t[image.w * image.h * 3];
    for (int y = 0; y < image.h; ++y) {
        for (int x = 0; x < image.w; ++x) {
            int i = y * image.w + x;
            data[i * 3 + 0] = (uint8_t)(fmin(fmax(image.colors[i].r * 255.0, 0.0), 255.0));
            data[i * 3 + 1] = (uint8_t)(fmin(fmax(image.colors[i].g * 255.0, 0.0), 255.0));
            data[i * 3 + 2] = (uint8_t)(fmin(fmax(image.colors[i].b * 255.0, 0.0), 255.0));
        }
    }

    stbi_write_png("renders/image.png", image.w, image.h, 3, data, image.w * 3);

    return 0;
}
