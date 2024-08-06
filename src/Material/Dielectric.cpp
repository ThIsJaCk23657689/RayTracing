#include "Entity/HittableList.hpp"
#include "Material/Dielectric.hpp"

bool Dielectric::Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const {
	attenuation = color(1.0, 1.0, 1.0);
    double ri = record.m_is_front_face ? (1.0 / m_refractive_index) : m_refractive_index;

	vec3 unit_direction = normalize(r.m_direction);
    vec3 refracted = refract(unit_direction, record.m_normal, ri);

	scattered = Ray(record.m_hit_point, refracted);
    return true;
}