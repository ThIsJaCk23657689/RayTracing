#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Utility/Helper.hpp"

struct Image {
    unsigned int m_width;
    unsigned int m_height;

    Image(const unsigned int& width, const unsigned int& height);
    ~Image() = default;

    color GetColor(const int& x, const int& y) const;
    void SetColor(const color& color, const int& x, const int& y);
    virtual void Export(const std::string& path) = 0;

protected:
    std::vector<color> m_colors;

};

#endif