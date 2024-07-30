#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Utility/Helper.hpp"
#include "Ray.hpp"

struct HitRecord;

class Material {
public:
    virtual bool Scatter(const Ray& r, const HitRecord& record, color& attenuation, Ray& scattered) const = 0;

};

#endif
