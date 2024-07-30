#include "Renderer.hpp"
#include "Utility/Helper.hpp"
#include <iostream>

void Renderer::Render(Image& image, const Camera& camera, const HittableList& world, const unsigned int& samples_per_pixel, unsigned int depth) {
    std::cout << "\nStarting render..." << std::endl;

    const int progress_bar_length = 70;
    int current_progress_bar_count = 0;
    float progress = 0.0f;
    for (int j = 0; j < image.m_height; j++) {

        progress = static_cast<float>(j + 1) / static_cast<float>(image.m_height);
        current_progress_bar_count = static_cast<int>(progress_bar_length * progress);
        std::cout << "[";
        for (int n = 0; n < progress_bar_length; n++) {
            if (n == current_progress_bar_count) {
                std::cout << ">";
                continue;
            }
            if (n < current_progress_bar_count) {
                std::cout << "=";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "] " << static_cast<int>(100.0f * progress) << "%\r" << std::flush;

        for (int i = 0; i < image.m_width; i++) {
            color pixel_color(0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (i + random_double()) / (image.m_width - 1);
                auto v = (j + random_double()) / (image.m_height - 1);

                Ray r = camera.GetRay(u, v);
                pixel_color += RayColor(r, world, depth);
            }

            // Antialiasing and Gamma Correction
            auto scale = 1.0 / samples_per_pixel;
            pixel_color.r = std::sqrt(pixel_color.r * scale);
            pixel_color.g = std::sqrt(pixel_color.g * scale);
            pixel_color.b = std::sqrt(pixel_color.b * scale);
            pixel_color = clamp(pixel_color, 0.0, 0.999);

            image.SetColor(pixel_color, i, j);
        }
    }
    image.Export("assets/images/result");
}

color Renderer::RayColor(const Ray& r, const HittableList& world, unsigned int depth) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) return { 0.0, 0.0, 0.0 };

    HitRecord record;

    if (world.Hit(r, Interval(0, Infinity), record)) {
        Ray scattered;
        color attenuation;
        if (record.m_material_ptr->Scatter(r, record, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
        return { 0, 0, 0 };
    }

    vec3 unit_dir = normalize(r.m_direction);
    auto t = 0.5 * (unit_dir.y + 1.0);
    return lerp({1.0, 1.0, 1.0}, {0.5, 0.7, 1.0}, t);
}