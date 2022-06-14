#include <iostream>

#include "Ray.hpp"
#include "Image/BMP.hpp"
#include "Entity/Sphere.hpp"
#include "Entity/HittableList.hpp"
#include "Utility/Helper.hpp"

color RayColor(const Ray& r, const Hittable& world) {
    HitRecord record;
    if (world.Hit(r, 0, Infinity, record)) {
        return 0.5 * (record.m_normal + 1);
    }

    vec3 unit_dir = normalize(r.m_direction);
    auto t = 0.5 * (unit_dir.y + 1.0);
    return lerp({1.0, 1.0, 1.0}, {0.5, 0.7, 1.0}, t);
}

int main(int argc, char** argv) {
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.Add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Renderer
    BMP my_image(image_width, image_height);
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto u = static_cast<double>(i) / (image_width - 1);
            auto v = static_cast<double>(j) / (image_height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = RayColor(r, world);

            my_image.SetColor(pixel_color, i, j);
        }
    }
    my_image.Export("assets/images/result.bmp");

    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}