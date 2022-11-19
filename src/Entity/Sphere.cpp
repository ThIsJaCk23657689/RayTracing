#include "Entity/Sphere.hpp"
#include <cmath>

bool Sphere::Hit(const Ray& r, const double& t_min, const double& t_max, HitRecord& record) const {
    vec3 oc = r.m_origin - m_center;
    auto a = r.m_direction.length_squared();
    auto half_b = dot(oc, r.m_direction);
    auto c = oc.length_squared() - m_radius * m_radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;

    auto sqrt_d = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrt_d) / a;
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrt_d) / a;
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    record.m_t = root;
    record.m_hit_point = r.At(record.m_t);
    vec3 outward_normal = (record.m_hit_point - m_center) / m_radius;
    record.SetFaceNormal(r, outward_normal);
    record.m_material_ptr = m_material_ptr;

    return true;
}