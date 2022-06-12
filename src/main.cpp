#include <iostream>

#include "Image/BMP.hpp"
#include "Image/PPM.hpp"

int main(int argc, char** argv) {
    const int image_width = 512;
    const int image_height = 512;

    BMP my_image(image_width, image_height);
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto r = static_cast<float>(i) / static_cast<float>(image_width - 1);
            auto g = static_cast<float>(j) / static_cast<float>(image_height - 1);
            auto b = 0.25f;

            my_image.SetColor({r, g, b}, i, j);
        }
    }
    my_image.Export("assets/images/result.bmp");


    PPM my_image_2(image_width, image_height);
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto r = static_cast<float>(i) / static_cast<float>(image_width - 1);
            auto g = static_cast<float>(j) / static_cast<float>(image_height - 1);
            auto b = 0.0f;

            my_image_2.SetColor({r, g, b}, i, j);
        }
    }
    my_image_2.Export("assets/images/result.ppm");

    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}