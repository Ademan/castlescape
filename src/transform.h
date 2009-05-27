#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GL/gl.h>
#include <cml/cml.h>
#include "math_types.h"

using cml::matrix_rotation_euler;

struct euler_rotation_t
{
    vec3 angles;
    void apply()
    {
        mat4 result;
        matrix_rotation_euler(result, angles[0], angles[1], angles[2], cml::euler_order_yxz);
        cml::identity_transform(result);
        
    }
};

struct translation_t
{
    vec3 position;
    void apply()
    {
        mat4 result;
        cml::matrix_translation(result, position);
        glMultMatrixf(result.data());
    }
};

struct scaling_t
{
    vec3 scaling;
    void apply()
    {
        mat4 result;
        cml::matrix_scale(result, scaling);
        glMultMatrixf(result.data());
    }
}; 

template <typename rotation_t = euler_rotation_t>
struct transform_t
{
    rotation_t      rotation;
    translation_t   position;
    scaling_t       scaling;
    
    void apply()
    {
        //glPushMatrix();
        position.apply();
        scaling.apply();
    }
};

#endif /*TRANSFORM_H*/
