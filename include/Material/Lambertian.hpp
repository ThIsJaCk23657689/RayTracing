#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "Material/Material.hpp"

class Lambertian : public Material {
public:
    Lambertian(const color& albedo) : m_albedo(albedo) {}
    bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const override;
    
private:
    color m_albedo;
};

#endif