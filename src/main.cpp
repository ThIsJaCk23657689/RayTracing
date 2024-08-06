#include "Utility/Helper.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Image/BMP.hpp"
#include "Entity/HittableList.hpp"
#include "Entity/Sphere.hpp"
#include "Utility/Timer.hpp"
#include "Utility/ArgumentParser.hpp"
#include "Material/Lambertian.hpp"
#include "Material/Metal.hpp"
#include "Material/Dielectric.hpp"

int main(int argc, char** argv) {

    try {
        ArgumentParser::Parse(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "ray_tracing: " << e.what() << std::endl;
        std::cerr << "Usage: ray_tracing \n\t[ -w | -W | -Width ] <width> \n\t[ -s | -S | -Samples ] <samples> \n\t[ -d | -D | -Depth ] <max_depth>" << std::endl;
        return -1;
    }

    Timer main_timer;

    // Configure settings
    const auto aspect_ratio = 16.0 / 9.0;
    const unsigned int image_width = ArgumentParser::image_width;
    const unsigned int image_height = std::max(static_cast<int>(image_width / aspect_ratio), 1);
    const unsigned int samples_per_pixel = ArgumentParser::samples_per_pixel;
    const unsigned int max_depth = ArgumentParser::max_depth;

    // World
    HittableList world;

    // Material
    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Dielectric>(1.50);
    auto material_bubble = std::make_shared<Dielectric>(1.0 / 1.50);
    auto material_right  = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);

    world.Add(std::make_shared<Sphere>(point3( 0.0,  -100.5, -1.0), 100.0, material_ground));
    world.Add(std::make_shared<Sphere>(point3( 0.0,     0.0, -1.2),   0.5, material_center));
    world.Add(std::make_shared<Sphere>(point3(-1.0,     0.0, -1.0),   0.5, material_left));
    world.Add(std::make_shared<Sphere>(point3(-1.0,     0.0, -1.0),   0.4, material_bubble));
    world.Add(std::make_shared<Sphere>(point3( 1.0,     0.0, -1.0),   0.5, material_right));

    // Camera
    Camera camera(image_width, image_height);

    // Renderer
    main_timer.Start();
    BMP my_image(image_width, image_height);
    Renderer::Render(my_image, {camera, world, samples_per_pixel, max_depth});
    main_timer.Print("Render image completed");

    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}