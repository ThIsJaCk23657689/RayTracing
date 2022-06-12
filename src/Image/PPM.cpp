#include "Image/PPM.hpp"
#include <iostream>

PPM::PPM(const int& width, const int& height) : Image(width, height) {
}

void PPM::Export(const std::string& path) {
    std::ofstream output(path);
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
            int r = static_cast<int>(GetColor(x, y).r * 255.0f);
            int g = static_cast<int>(GetColor(x, y).g * 255.0f);
            int b = static_cast<int>(GetColor(x, y).b * 255.0f);

            output << r << " " << g << " " << b << std::endl;
        }
    }

    output.close();
    std::cout << "\nPPM file save successfully." << std::endl;
}