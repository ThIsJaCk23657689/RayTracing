#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Entity/Hittable.hpp"
#include "Utility/vec3.hpp"
#include "Material/Material.hpp"
#include <memory>
#include <utility>

class Sphere : public Hittable {
public:
    Sphere() = default;
    Sphere(const point3& center, const double& radius, std::shared_ptr<Material> material) :
        m_center(center), 
        m_radius(std::fmax(0, radius)), 
        m_material_ptr(material) 
    {
    }

    bool Hit(const Ray& r, const Interval& ray_t, HitRecord& record) const override;

    point3 m_center;
    double m_radius;
    std::shared_ptr<Material> m_material_ptr;
};

#endif