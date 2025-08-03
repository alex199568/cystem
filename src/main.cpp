#include <stdio.h>


#include "vector.hpp"
#include "point.hpp"
#include "color.hpp"
#include "image.hpp"



int main() {
    printf("Cystem\n");

    Image image(128, 96);

    for (int y = 10; y < 30; ++y) {
        for (int x = 20; x < 80; ++x) {
            image.set(x, y, red);
        }
    }

    image.save("renders/image.png");

    return 0;
}
