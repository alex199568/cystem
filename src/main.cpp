#include <stdio.h>


#include "vector.hpp"
#include "point.hpp"
#include "color.hpp"
#include "image.hpp"
#include "matrix.hpp"

void render() {
    Image image(128, 96);

    for (int y = 10; y < 30; ++y) {
        for (int x = 20; x < 80; ++x) {
            image.set(x, y, red);
        }
    }

    image.save("renders/image.png");
}

int main() {
    printf("Cystem\n");

    auto tr = translation(1, 2.0, -2.3);
    auto s = scale(0.4, 0.2, 4);

    tr.print();
    printf("\n");
    s.print();
    printf("\n");

    auto result = tr * s;
    result.print();
    printf("\n");

    auto t = result.transpose();
    t.print();


    return 0;
}
