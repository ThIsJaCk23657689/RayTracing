#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"

struct Camera {
    Camera(const double& aspect_ratio);

    Ray GetRay(const double& u, const double& v) const;

private:
    point3 m_position;
    point3 m_lower_left_corner;
    vec3 m_horizontal;
    vec3 m_vertical;

};
#endif