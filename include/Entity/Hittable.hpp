#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"

struct HitRecord {
    double m_t;
    vec3 m_normal;
    point3 m_hit_point;
    bool m_is_front_face;

    inline void SetFaceNormal(const Ray& r, const vec3& outward_normal) {
        m_is_front_face = dot(r.m_direction, outward_normal) < 0;
        m_normal = m_is_front_face ? outward_normal : -outward_normal ;
    };
};

struct Hittable {
    virtual bool Hit(const Ray& r, const double& t_min, const double& t_max, HitRecord& record) const = 0;
};

#endif