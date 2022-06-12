#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

struct vec3 {
    union {
        double val[3];
        struct { double x, y, z; };
        struct { double r, g, b; };
    };

    vec3();
    vec3(const double& _x, const double& _y, const double& _z);
    ~vec3() = default;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);
    vec3& operator*=(const double& t);
    vec3& operator/=(const double& t);
    double length() const;
    double length_squared() const;

};

// Type aliases for vec3
using point3 = vec3;
using color = vec3;

// vec3 utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << " " << v.y << " " << v.z;
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return { u.x + v.x, u.y + v.y, u.z + v.z };
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return { u.x - v.x, u.y - v.y, u.z - v.z };
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return { u.x * v.x, u.y * v.y, u.z * v.z };
}

inline vec3 operator*(const double& t, const vec3& v) {
    return { t * v.x, t * v.y, t * v.z };
}

inline vec3 operator*(const vec3& v, const double& t) {
    return t * v;
}

inline vec3 operator/(vec3 v, const double& t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return {u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x };
}

inline vec3 normalize(vec3 v) {
    return v / v.length();
}

#endif