#ifndef METAL_HPP
#define METAL_HPP

#include "Material/Material.hpp"

class Metal : public Material {
public:
    Metal(const color& albdeo, double fuzz) : m_albedo(albdeo), m_fuzz(fuzz < 1 ? fuzz : 1) {}
    virtual bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const override;
    
private:
    color m_albedo;
    double m_fuzz = 0.0;

};

#endif