#ifndef HELPER_HPP
#define HELPER_HPP

#include <limits>

// constants
const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// utility functions
inline double radians(const double& degrees) {
    return degrees * PI / 180.0;
}

#endif