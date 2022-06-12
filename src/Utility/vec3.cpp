#include "Utility/vec3.hpp"
#include <cassert>

vec3::vec3() : x(0), y(0), z(0) {}

vec3::vec3(const double& _x, const double& _y, const double& _z) : x(_x), y(_y), z(_z) {}

vec3 vec3::operator-() const {
    return { -x, -y, -z };
}

double vec3::operator[](int i) const {
    assert(i > 0 && i < 3);
    return val[i];
}

double& vec3::operator[](int i) {
    assert(i > 0 && i < 3);
    return val[i];
}

vec3& vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3& vec3::operator*=(const double& t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

vec3& vec3::operator/=(const double& t) {
    return *this *= 1/t;
}

double vec3::length() const {
    return std::sqrt(length_squared());
}

double vec3::length_squared() const {
    return x * x + y * y + z * z;
}