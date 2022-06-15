#include "Renderer.hpp"
#include "Utility/Helper.hpp"
#include <iostream>

void Renderer::Render(Image& image, const Camera& camera, const HittableList& world, const unsigned int& samples_per_pixel) {
    std::cout << "Starting render..." << std::endl;
    for (int j = 0; j < image.m_height; j++) {
        std::cerr << "\rProgress: " << j << " " << std::flush;
        for (int i = 0; i < image.m_width; i++) {
            color pixel_color(0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (i + random_double()) / (image.m_width - 1);
                auto v = (j + random_double()) / (image.m_height - 1);

                Ray r = camera.GetRay(u, v);
                pixel_color += RayColor(r, world);
            }

            // Antialiasing
            auto scale = 1.0 / samples_per_pixel;
            pixel_color *= scale;
            pixel_color = clamp(pixel_color, 0.0, 0.999);

            image.SetColor(pixel_color, i, j);
        }
    }
    image.Export("assets/images/result");
}

color Renderer::RayColor(const Ray& r, const HittableList& world) {
    HitRecord record;
    if (world.Hit(r, 0, Infinity, record)) {
        return 0.5 * (record.m_normal + 1);
    }

    vec3 unit_dir = normalize(r.m_direction);
    auto t = 0.5 * (unit_dir.y + 1.0);
    return lerp({1.0, 1.0, 1.0}, {0.5, 0.7, 1.0}, t);
}