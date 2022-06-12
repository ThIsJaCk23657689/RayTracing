#ifndef BMP_HPP
#define BMP_HPP

#include <string>
#include <fstream>
#include <cstddef>
#include "Image/Image.hpp"

struct BMP : public Image {
    BMP(const int& width, const int& height);
    ~BMP() = default;

    void Export(const std::string& path) override;

};

#endif