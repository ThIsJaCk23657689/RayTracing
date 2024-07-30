#ifndef METAL_HPP
#define METAL_HPP

#include "Material/Material.hpp"
#include "Utility/vec3.hpp"

class Metal : public Material {
public:
    Metal(const color& albdeo) : m_albedo(albdeo) {}
    virtual bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const override;
    
private:
    color m_albedo;

};

#endif