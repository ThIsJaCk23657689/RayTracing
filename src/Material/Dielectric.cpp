#include "Entity/HittableList.hpp"
#include "Material/Dielectric.hpp"

bool Dielectric::Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const {
	attenuation = color(1.0, 1.0, 1.0);
    double ri = record.m_is_front_face ? (1.0 / m_refractive_index) : m_refractive_index;

	vec3 unit_direction = normalize(r.m_direction);
    double cos_theta = std::fmin(dot(-unit_direction, record.m_normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;

    vec3 direction;
    if (cannot_refract || Reflectance(cos_theta, ri) > random_double()) {
        direction = reflect(unit_direction, record.m_normal);
    } else {
		direction = refract(unit_direction, record.m_normal, ri);
	}

	scattered = Ray(record.m_hit_point, direction);
    return true;
}

double Dielectric::Reflectance(double cosine, double refraction_index) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}