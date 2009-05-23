#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <cml/cml.h>
#include "math_types.h"

using cml::matrix_rotation_quaternion;
using cml::matrix_rotation_euler;
using cml::matrix_translation;

class Camera
{
    vec3     pos;
    float    pitch;
    float    yaw;
public:
    Camera(): pos(0, 0, 0), pitch(0), yaw(0) {}
    const mat4     get_mat()
    {
        mat4 rotation;

        float roll = 0;
        matrix_rotation_euler(rotation, yaw, pitch, roll, cml::euler_order_yxz);

        mat4     translation;
        matrix_translation(translation, -pos);

        return rotation * translation;
    }
    void setpos(const vec3 & v)
    {
        pos = v;
    }
    void rotate(float _yaw, float _pitch)
    {
        yaw += _yaw;
        pitch += _pitch;
    }
    void move(const vec3 & v)
    {
        cmat3    rotation;

        float roll = 0;
        matrix_rotation_euler(rotation, yaw, pitch, roll, cml::euler_order_yxz);
        
        pos -= rotation * v;
    }
    void collide()
    {
        if (pos[1] < 0) pos[1] = 0;
    }
};

#endif
