#ifndef BMP_HPP
#define BMP_HPP

#include "Image/Image.hpp"

struct BMP : public Image {
    BMP(const unsigned int& width, const unsigned int& height);
    ~BMP() = default;

    void Export(const std::string& path) override;

};

#endif