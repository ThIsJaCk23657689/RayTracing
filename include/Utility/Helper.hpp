#ifndef HELPER_HPP
#define HELPER_HPP

#include <cmath>
#include <limits>
#include <random>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

// constants
const double PI = 3.1415926535897932385;

// utility functions
inline double radians(const double& degrees) {
    return degrees * PI / 180.0;
}

template< typename T >
inline T clamp(const T& x, const T& min, const T& max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double linear_to_gamma(const double& input) {
    // pow(input, 1/gamma) where gamma = 2.2. there we simply take the square root.
    if (input > 0) return std::sqrt(input);
    return 0;
}

inline double random_double() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double random_double(const double& min, const double& max) {
    return min + (max - min) * random_double();
}

// common header
#include "vec3.hpp"
#include "Interval.hpp"

#endif