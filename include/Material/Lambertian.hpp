#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "Material/Material.hpp"

class Lambertian : public Material {
public:
    Lambertian(const color& a) : m_albedo(a) {}
    bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const override;
    color m_albedo;
};

#endif