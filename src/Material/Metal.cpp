#include "Material/Metal.hpp"

bool Metal::Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const {
    vec3 reflected = reflect(r.m_direction, record.m_normal);
    scattered = Ray(record.m_hit_point, reflected);
    attenuation = m_albedo;
    return true;
}