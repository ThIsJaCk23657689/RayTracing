#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include "Utility/vec3.hpp"
// #include "Utility/Color.hpp"

struct Image {
    Image(const int& width, const int& height);
    ~Image() = default;

    color GetColor(const int& x, const int& y) const;
    void SetColor(const color& color, const int& x, const int& y);
    virtual void Export(const std::string& path) = 0;

protected:
    int m_width;
    int m_height;
    std::vector<color> m_colors;

};

#endif