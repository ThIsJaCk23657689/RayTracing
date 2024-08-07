#include "Material/Metal.hpp"
#include "Entity/HittableList.hpp"

bool Metal::Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const {
    vec3 reflected = reflect(r.m_direction, record.m_normal);
    reflected = normalize(reflected) + (m_fuzz * random_unit_vector());
    scattered = Ray(record.m_hit_point, reflected);
    attenuation = m_albedo;
    return (dot(scattered.m_direction, record.m_normal) > 0);
}