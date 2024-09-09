#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"

struct CameraDesc {
    unsigned int width = 1920;
    unsigned int height = 1080;

    double fovy = 90;

    vec3 position = { 0, 0, 1 };
    vec3 lookat = { 0, 0, 0 };
    vec3 world_up = { 0, 1, 0 };
};

struct Camera {
public:
    Camera(const CameraDesc& desc);

    Ray GetRay(int i, int j) const;

private:
    vec3 GetRandomOffset() const;

    point3 m_center;	        // camera center

    point3 m_pixel00_location;  // location of pixel 0, 0
    vec3 m_pixel_delta_u;       // offset to pixel to the right
    vec3 m_pixel_delta_v;       // offset to pixel below 

    vec3 u, v, w;               // Camera frame basis vectors

};
#endif