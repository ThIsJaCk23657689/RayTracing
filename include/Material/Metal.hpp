#ifndef METAL_HPP
#define METAL_HPP

#include "Material/Material.hpp"
#include "Utility/vec3.hpp"

class Metal : public Material {
public:
    Metal(const color& a) : m_albedo(a) {}
    virtual bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const override;
    color m_albedo;
};

#endif