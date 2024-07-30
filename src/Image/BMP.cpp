#include "Image/BMP.hpp"
#include "Utility/Interval.hpp"
#include <iostream>

inline double linear_to_gamma(const double& input) {
    if (input > 0) 
        return std::sqrt(input);

    return 0;
}

inline color linear_to_gamma(const color& linear) { 
    return color(linear_to_gamma(linear.r), linear_to_gamma(linear.g), linear_to_gamma(linear.b));
}

BMP::BMP(const unsigned int& width, const unsigned int& height) : Image(width, height) {
}

void BMP::Export(const std::string& path) {
    std::cout << "\nStarting export..." << std::endl;
    std::ofstream output(path + ".bmp", std::ios::binary);
    if (!output.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const auto padding_amount = ((4 - (m_width * 3) % 4) % 4);

    const auto file_header_size = 14;
    const auto info_header_size = 40;
    const auto image_size = m_width * m_height * 3 + padding_amount * m_height;
    const auto file_size = file_header_size + info_header_size + image_size;

    // File Header
    unsigned char file_header[file_header_size];
    // file type
    file_header[0] = 'B';
    file_header[1] = 'M';

    // file size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;

    // reserved 1
    file_header[6] = 0;
    file_header[7] = 0;

    // reserved 2
    file_header[8] = 0;
    file_header[9] = 0;

    // pixel data offset
    file_header[10] = file_header_size + info_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    // Info Header (DIB)
    unsigned char info_header[info_header_size];
    // info header size
    info_header[0] = info_header_size;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;

    // image width
    info_header[4] = m_width;
    info_header[5] = m_width >> 8;
    info_header[6] = m_width >> 16;
    info_header[7] = m_width >> 24;

    // image height
    info_header[8] = m_height;
    info_header[9] = m_height >> 8;
    info_header[10] = m_height >> 16;
    info_header[11] = m_height >> 24;

    // planes
    info_header[12] = 1;
    info_header[13] = 0;

    // bits per pixel
    info_header[14] = 24;
    info_header[15] = 0;

    // compression
    info_header[16] = 0;
    info_header[17] = 0;
    info_header[18] = 0;
    info_header[19] = 0;

    // image size
    info_header[20] = 0;
    info_header[21] = 0;
    info_header[22] = 0;
    info_header[23] = 0;

    // X pixels per meter
    info_header[24] = 0;
    info_header[25] = 0;
    info_header[26] = 0;
    info_header[27] = 0;

    // Y pixels per meter
    info_header[28] = 0;
    info_header[29] = 0;
    info_header[30] = 0;
    info_header[31] = 0;

    // total color (color palette not used)
    info_header[32] = 0;
    info_header[33] = 0;
    info_header[34] = 0;
    info_header[35] = 0;

    // important color (generally ignored)
    info_header[36] = 0;
    info_header[37] = 0;
    info_header[38] = 0;
    info_header[39] = 0;

    output.write(reinterpret_cast<const char*>(file_header), file_header_size);
    output.write(reinterpret_cast<const char*>(info_header), info_header_size);

    // Image Data
    for (int y = 0; y < m_height; y++) {
        std::cerr << "\rProgress: " << y << " " << std::flush;
        for (int x = 0; x < m_width; x++) {
            auto pixel_color = GetColor(x, y);
            auto gamma_corrected = linear_to_gamma(pixel_color);
            
            static const Interval intensity(0.000, 0.999);
            unsigned char r = static_cast<unsigned char>(intensity.Clamp(gamma_corrected.r) * 256);
            unsigned char g = static_cast<unsigned char>(intensity.Clamp(gamma_corrected.g) * 256);
            unsigned char b = static_cast<unsigned char>(intensity.Clamp(gamma_corrected.b) * 256);

            unsigned char color[] = {b, g, r};
            output.write(reinterpret_cast<const char*>(color), 3);
        }
        output.write(reinterpret_cast<const char*>(bmp_pad), padding_amount);
    }

    output.close();
    std::cout << "\nBMP file save successfully." << std::endl;
}