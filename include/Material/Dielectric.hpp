#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "Material/Material.hpp"

class Dielectric : public Material {
public:
    Dielectric(double refractive_index) : m_refractive_index(refractive_index) {}
    virtual bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const override;

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refreactive index of the enclosing media.
    double m_refractive_index;

    static double Reflectance(double cosine, double refraction_index);

};

#endif