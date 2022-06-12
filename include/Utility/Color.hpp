#ifndef COLOR_HPP
#define COLOR_HPP

struct Color {
    float r, g, b;

    Color();
    Color(const float& _r, const float& _g, const float& _b);
    ~Color() = default;
};

#endif