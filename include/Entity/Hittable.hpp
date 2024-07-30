#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "Material/Material.hpp"
#include "Utility/Interval.hpp"
#include <memory>

class Material;

struct HitRecord {
    point3 m_hit_point;
    vec3 m_normal;
    std::shared_ptr<Material> m_material_ptr;
    double m_t;
    bool m_is_front_face;

    inline void SetFaceNormal(const Ray& r, const vec3& outward_normal) {
        m_is_front_face = dot(r.m_direction, outward_normal) < 0;
        m_normal = m_is_front_face ? outward_normal : -outward_normal ;
    };
};

struct Hittable {
    virtual bool Hit(const Ray& r, const Interval& ray_t, HitRecord& record) const = 0;
};

#endif