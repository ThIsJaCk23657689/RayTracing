#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include "Utility/Color.hpp"

struct Image {
    Image(const int& width, const int& height);
    ~Image() = default;

    Color GetColor(const int& x, const int& y) const;
    void SetColor(const Color& color, const int& x, const int& y);
    virtual void Export(const std::string& path) = 0;

protected:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;

};

#endif