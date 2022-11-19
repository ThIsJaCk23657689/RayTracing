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
    Sphere(const point3& center, const double& radius, std::shared_ptr<Material> material)
        : m_center(center), m_radius(radius), m_material_ptr(std::move(material)) {}

    bool Hit(const Ray& r, const double& t_min, const double& t_max, HitRecord& record) const override;

    point3 m_center;
    double m_radius;
    std::shared_ptr<Material> m_material_ptr;
};

#endif