#ifndef HELPER_HPP
#define HELPER_HPP

#include <limits>
#include <random>

// constants
const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// utility functions
inline double radians(const double& degrees) {
    return degrees * PI / 180.0;
}

inline double clamp(const double& x, const double& min, const double& max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
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

template< typename T >
inline T clamp(const T& x, const T& min, const T& max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
#endif