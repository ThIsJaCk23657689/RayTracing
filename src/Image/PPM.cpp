#include "Image/PPM.hpp"
#include <iostream>
#include <fstream>

PPM::PPM(const unsigned int& width, const unsigned int& height) : Image(width, height) {
}

void PPM::Export(const std::string& path) {
    std::cout << "\nStarting export..." << std::endl;
    std::ofstream output(path + ".ppm");
    if (!output.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    output << "P3" << std::endl;
    output << m_width << " " << m_height << std::endl;
    output << "255" << std::endl;

    for (int y = m_height - 1; y >= 0; y--) {
        std::cerr << "\rProgress: " << m_height - 1 - y << " " << std::flush;
        for (int x = 0; x < m_width; x++) {
            int r = static_cast<int>(GetColor(x, y).r * 256.0f);
            int g = static_cast<int>(GetColor(x, y).g * 256.0f);
            int b = static_cast<int>(GetColor(x, y).b * 256.0f);

            output << r << " " << g << " " << b << std::endl;
        }
    }

    output.close();
    std::cout << "\nPPM file save successfully." << std::endl;
}