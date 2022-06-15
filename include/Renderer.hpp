#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Image/Image.hpp"
#include "Camera.hpp"
#include "Entity/HittableList.hpp"

struct Renderer {
    static void Render(Image& image, const Camera& camera, const HittableList& world, const unsigned int& samples_per_pixel);

private:
    static color RayColor(const Ray& r, const HittableList& world);

};

#endif