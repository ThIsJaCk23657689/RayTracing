#include <iostream>

#include "Ray.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Image/BMP.hpp"
#include "Entity/Sphere.hpp"
#include "Entity/HittableList.hpp"

int main(int argc, char** argv) {
    // Configure settings
    const auto aspect_ratio = 16.0 / 9.0;
    const unsigned int image_width = 400;
    const unsigned int image_height = static_cast<int>(image_width / aspect_ratio);
    const unsigned int samples_per_pixel = 100;
    const unsigned int max_depth = 50;

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Camera
    Camera camera(aspect_ratio);

    // Renderer
    BMP my_image(image_width, image_height);
    Renderer::Render(my_image, camera, world, samples_per_pixel, max_depth);

    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}