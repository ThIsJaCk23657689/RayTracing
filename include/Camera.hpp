#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"

struct Camera {
public:
    Camera(unsigned int width, unsigned int height);

    Ray GetRay(int i, int j) const;

private:
    vec3 GetRandomOffset() const;

    point3 m_position;	        // camera center

    point3 m_pixel00_location;  // location of pixel 0, 0
    vec3 m_pixel_delta_u;       // offset to pixel to the right
    vec3 m_pixel_delta_v;       // offset to pixel below    

};
#endif