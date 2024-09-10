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

    // ground
    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(point3(0.0, -1000, 0.0), 1000.0, ground_material));

    // small random ball
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    // Material
    auto material_1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material_1));

    auto material_2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material_2));

    auto material_3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material_3));

    // Camera
    CameraDesc camera_desc;
    camera_desc.width = image_width;
    camera_desc.height = image_height;
    camera_desc.fovy = 20;

    camera_desc.position = { 13, 2, 3 };
    camera_desc.lookat = { 0, 0, 0 };
    camera_desc.world_up = { 0, 1, 0 };

    camera_desc.defocus_angle = 0.6;
    camera_desc.focus_distance = 10.0;
    Camera camera(camera_desc);

    // Renderer
    main_timer.Start();
    BMP my_image(image_width, image_height);
    Renderer::Render(my_image, {camera, world, samples_per_pixel, max_depth});
    main_timer.Print("Render image completed");

    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}