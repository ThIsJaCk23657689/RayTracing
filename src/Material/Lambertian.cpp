#include "Material/Lambertian.hpp"
#include "Entity/HittableList.hpp"

bool Lambertian::Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const {
    auto scatter_direction = record.m_normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero()) {
        scatter_direction = record.m_normal;
    }

    scattered = Ray(record.m_hit_point, scatter_direction);
    attenuation = m_albedo;
    return true;
}