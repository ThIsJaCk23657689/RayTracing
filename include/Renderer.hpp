#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Utility/Helper.hpp"
#include "Ray.hpp"
#include <mutex>
#include <atomic>

struct Image;
struct Camera;
struct HittableList;

struct RenderDesc {
	const Camera& camera;
	const HittableList& world;
	const unsigned int& samples_per_pixel;
	const unsigned int& depth;
};

struct Renderer {
    static std::mutex image_mutex;
    static std::mutex progress_mutex;
    static std::atomic<int> completed_row;
    static const int32_t progress_bar_width;
    static void Render(Image& image, const RenderDesc& render_desc);

private:
    static void RenderRows(Image& image, const RenderDesc& render_desc, Interval<int32_t> row_interval);
    static void RenderRow(Image& image, const RenderDesc& render_desc, int32_t current_row);
    static color RayColor(const Ray& r, const HittableList& world, unsigned int depth);
    static color GammaCorrect(const color& linear);
    static void UpdateProgressBar(int progress, int total);

};

#endif