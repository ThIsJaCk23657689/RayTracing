#include "Camera.hpp"

Camera::Camera(const double& aspect_ratio) {
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    m_position = point3(0, 0, 0);
    m_horizontal = vec3(viewport_width, 0, 0);
    m_vertical = vec3(0, viewport_height, 0);
    m_lower_left_corner = m_position - m_horizontal / 2 - m_vertical / 2 - vec3(0, 0, focal_length);
}

Ray Camera::GetRay(const double& u, const double& v) const {
    return Ray(m_position, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_position);
}