#ifndef PPM_HPP
#define PPM_HPP

#include "Image/Image.hpp"

struct PPM : public Image {
    PPM(const unsigned int& width, const unsigned int& height);
    ~PPM() = default;

    void Export(const std::string& path) override;

};

#endif