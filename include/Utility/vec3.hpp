#ifndef VEC3_HPP
#define VEC3_HPP

#include "Utility/Helper.hpp"

struct vec3 {
    union {
        double val[3];
        struct { double x, y, z; };
        struct { double r, g, b; };
    };

    vec3();
    vec3(const double& scalar);
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
    bool near_zero() const;

    inline static vec3 random() {
        return { random_double(), random_double(), random_double() };
    }

    inline static vec3 random(const double& min, const double& max) {
        return { random_double(min, max), random_double(min, max), random_double(min, max) };
    }
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

inline vec3 lerp(const vec3& start, const vec3& end, const double& t) {
    return (1.0 - t) * start + t * end;
}

inline vec3 clamp(const vec3& v, const double& min, const double& max) {
    auto x = clamp(v.x, min, max);
    auto y = clamp(v.y, min, max);
    auto z = clamp(v.z, min, max);
    return {x, y, z};
}

inline vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return normalize(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) {
        // In the same hemisphere as the normal
        return in_unit_sphere;
    } else {
        return -in_unit_sphere;
    }
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

// make sure normal is an unit vector
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

// make sure uv and n are unit vector
// etai_over_etat = refractive index ratio which is etai/etat
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_para = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_para;
}


#endif