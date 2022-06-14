#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Entity/Hittable.hpp"
#include "Utility/vec3.hpp"

struct Sphere : public Hittable {
    point3 m_center;
    double m_radius;

    Sphere();
    Sphere(const point3& center, const double& radius);

    bool Hit(const Ray& r, const double& t_min, const double& t_max, HitRecord& record) const override;
};

#endif