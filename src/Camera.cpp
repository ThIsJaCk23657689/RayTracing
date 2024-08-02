#include "Camera.hpp"

Camera::Camera(const unsigned int width, const unsigned int height) {
    m_position = point3(0, 0, 0);

    // determine viewport dimensions.
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ((double) width / height);
    
    // calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, viewport_height, 0);
    
    // calculate the horizontal and vertical delta vectors from pixel to pixel.
    m_pixel_delta_u = viewport_u / width;
    m_pixel_delta_v = viewport_v / height;

    // calculate the location of the upper left pixel.
    auto viewport_upper_left = m_position - viewport_u / 2 - viewport_v / 2 - vec3(0, 0, focal_length);
    m_pixel00_location = viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);
}

Ray Camera::GetRay(int i, int j) const {
    // construct a ray originating from the origin and 
    // directed at ramdomly sampled point around the pixel localtion (i, j)

    auto offset = GetRandomOffset();
    auto pixel_sample = m_pixel00_location 
                        + ((i + offset.x) * m_pixel_delta_u)
                        + ((j + offset.y) * m_pixel_delta_v);

    auto ray_origin = m_position;
    auto ray_direction = pixel_sample - m_position;

    return Ray(ray_origin, ray_direction);
}

vec3 Camera::GetRandomOffset() const {
    // return the vector to a random point in the [-0.5, -0.5] ~ [+0.5, +0.5] unit square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}