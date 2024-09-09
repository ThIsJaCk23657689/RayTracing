#include "Camera.hpp"

Camera::Camera(const CameraDesc& desc) {
    auto& width = desc.width;
    auto& height = desc.height;

    m_center = desc.position;
    m_defocus_angle = desc.defocus_angle;

    // determine viewport dimensions.
    auto theta = radians(desc.fovy);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * desc.focus_distance;
    auto viewport_width = viewport_height * ((double) width / height);

    // calculate the u, v, w uint basis vectors for the camera coordinate frame.
    w = normalize(desc.position - desc.lookat);
    u = normalize(cross(desc.world_up, w));
    v = cross(w, u);
    
    // calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = viewport_width * u;   // vector across viewport horizontal edge
    auto viewport_v = viewport_height * v;  // vector down viewport vertical edge
    
    // calculate the horizontal and vertical delta vectors from pixel to pixel.
    m_pixel_delta_u = viewport_u / width;
    m_pixel_delta_v = viewport_v / height;

    // calculate the location of the upper left pixel.
    auto viewport_upper_left = m_center - viewport_u / 2 - viewport_v / 2 - (desc.focus_distance * w);
    m_pixel00_location = viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);

    // calculate the camera defocus disk basis vectors
    auto defocus_radius = desc.focus_distance * std::tan(radians(m_defocus_angle / 2));
    m_defocus_disk_u = u * defocus_radius;
    m_defocus_disk_v = v * defocus_radius;
}

Ray Camera::GetRay(int i, int j) const {
    // construct a camera ray originating from the defocus disk and directed at a
    // ramdomly sampled point around the pixel localtion (i, j)

    auto offset = GetRandomOffset();
    auto pixel_sample = m_pixel00_location 
                        + ((i + offset.x) * m_pixel_delta_u)
                        + ((j + offset.y) * m_pixel_delta_v);

    auto ray_origin = (m_defocus_angle <= 0) ? m_center : DefocusDiskSample() ;
    auto ray_direction = pixel_sample - m_center;

    return Ray(ray_origin, ray_direction);
}

vec3 Camera::GetRandomOffset() const {
    // return the vector to a random point in the [-0.5, -0.5] ~ [+0.5, +0.5] unit square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

vec3 Camera::DefocusDiskSample() const {
    // returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return m_center + (p.x * m_defocus_disk_u) + (p.y * m_defocus_disk_v);
}