#include "Image/Image.hpp"

Image::Image(const int& width, const int& height) :
    m_width(width), m_height(height), m_colors(std::vector<color>(width * height)) {
}

color Image::GetColor(const int& x, const int& y) const {
    return m_colors[y * m_width + x];
}

void Image::SetColor(const color& color, const int& x, const int& y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}