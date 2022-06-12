#ifndef PPM_HPP
#define PPM_HPP

#include <string>
#include <fstream>
#include <cstddef>
#include "Image/Image.hpp"

struct PPM : public Image {
    PPM(const int& width, const int& height);
    ~PPM() = default;

    void Export(const std::string& path) override;

};

#endif