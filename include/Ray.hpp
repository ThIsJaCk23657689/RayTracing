#ifndef RAY_HPP
#define RAY_HPP

#include "Utility/vec3.hpp"

struct Ray {
    point3 m_origin;
    vec3 m_direction;

    Ray();
    Ray(const point3& origin, const vec3& direction);

    point3 At(const double& t) const;
};

#endif