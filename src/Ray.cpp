#include "Ray.hpp"

Ray::Ray() : m_origin(0.0), m_direction(0.0, 0.0, -1.0) {
}

Ray::Ray(const point3& origin, const vec3& direction) : m_origin(origin), m_direction(direction) {
}

point3 Ray::At(const double& t) const {
    return m_origin + t * m_direction;
}