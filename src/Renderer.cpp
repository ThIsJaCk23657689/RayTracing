#include "Renderer.hpp"
#include "Utility/Helper.hpp"
#include "Camera.hpp"
#include "Image/Image.hpp"
#include "Material/Material.hpp"
#include "Entity/HittableList.hpp"
#include "Utility/Console.hpp"
#include <thread>

std::mutex Renderer::image_mutex;
std::mutex Renderer::progress_mutex;
std::atomic<int> Renderer::completed_row(0);
const int32_t Renderer::progress_bar_width = 70;

void Renderer::Render(Image& image, const RenderDesc& render_desc) {
    Console::Print("\nStarting render...");
    Console::Print("Image size: ( %d, %d )", image.m_width, image.m_height);
    Console::Print("Samples per pixel: %d", render_desc.samples_per_pixel);
    Console::Print("Max depth: %d", render_desc.depth);

    int current_progress_bar_count = 0;
    float progress = 0.0f;

    int num_threads = std::thread::hardware_concurrency();
    // int num_threads = 1;

    // 算出一個 thread 要處理幾行 row
    int rows_per_thread = std::ceil(static_cast<float>(image.m_height) / num_threads); 
   
    // 輸出 status
    Console::Print("\nThreads: %d", num_threads);
    Console::Print("Rows per thread: %d", rows_per_thread);

    std::vector<std::thread> threads;
    for (size_t t = 0; t < num_threads; t++) {
        int32_t start_row = t * rows_per_thread;
        int32_t end_row = std::min(start_row + rows_per_thread, (int)image.m_height);
        Interval<int32_t> row_interval(start_row, end_row);

        threads.push_back(std::thread(RenderRows, std::ref(image), std::ref(render_desc), row_interval));
    }

    // run all threads and wait
    for (auto& thread : threads) {
        thread.join();
	}

    image.Export("assets/images/result");
}

void Renderer::RenderRows(Image& image, const RenderDesc& render_desc, Interval<int32_t> row_interval) {
	for (int j = row_interval.m_min; j < row_interval.m_max; j++) {
        // update progress
        completed_row++;
        UpdateProgressBar(completed_row, image.m_height);

        // ray tracing for each row
        RenderRow(image, render_desc, j);
	}
}

void Renderer::RenderRow(Image& image, const RenderDesc& render_desc, int32_t current_row) {
    for (int i = 0; i < image.m_width; i++) {
        color pixel_color(0);

        // for each sample per pixel
        for (int s = 0; s < render_desc.samples_per_pixel; s++) {
            Ray r = render_desc.camera.GetRay(i, current_row);
            pixel_color += RayColor(r, render_desc.world, render_desc.depth);
        }

        // Antialiasing
        auto scale = 1.0 / render_desc.samples_per_pixel;
        pixel_color.r = pixel_color.r * scale;
        pixel_color.g = pixel_color.g * scale;
        pixel_color.b = pixel_color.b * scale;

        // Gamma Correction
        pixel_color = GammaCorrect(pixel_color);
        pixel_color = clamp(pixel_color, 0.0, 0.999);

        // make sure only one thread can update the image at a time
        std::lock_guard<std::mutex> lock(image_mutex);
        image.SetColor(pixel_color, i, current_row);
    }
}

color Renderer::RayColor(const Ray& r, const HittableList& world, unsigned int depth) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) return { 0.0, 0.0, 0.0 };

    HitRecord record;

    if (world.Hit(r, Interval<double>(0.001, Interval<double>::Infinity), record)) {
        Ray scattered;
        color attenuation;
        if (record.m_material_ptr->Scatter(r, record, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth - 1);
        }
        return { 0, 0, 0 };
    }

    // Background
    vec3 unit_dir = normalize(r.m_direction);
    auto t = 0.5 * (unit_dir.y + 1.0);
    return lerp({1.0, 1.0, 1.0}, {0.5, 0.7, 1.0}, t);
}

color Renderer::GammaCorrect(const color& linear) {
	return color(linear_to_gamma(linear.r), linear_to_gamma(linear.g), linear_to_gamma(linear.b));
}

void Renderer::UpdateProgressBar(int progress, int total)
{
    std::lock_guard<std::mutex> lock(progress_mutex);

	float progress_percentage = static_cast<float>(progress) / total;
    int current_progress_bar_count = static_cast<int>(progress_bar_width * progress_percentage);

	std::cout << "[";
	for (int n = 0; n < progress_bar_width; ++n) {
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
    std::cout << "] " << static_cast<int>(100.0f * progress_percentage) << "%\r" << std::flush;
}