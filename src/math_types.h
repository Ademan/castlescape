#pragma once
#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <cml/cml.h>

typedef cml::vector2f       vec2;

typedef cml::vector3f       vec3;
typedef cml::matrix33f_c    mat3;
typedef cml::matrix33f_r    cmat3;

typedef cml::vector4f       vec4;
typedef cml::matrix44f_c    mat4;

typedef cml::quaternionf_p  pquat;
typedef cml::quaternionf_n  nquat;

typedef pquat               quat;

/*
 *
 *  h1----------h2
 *  |     |     |
 *  |     |     |
 *  |     |     |
 *  |-----p-----|
 *  |     |     |
 *  |     |     |
 *  |     |     |
 *  h3----------h4
 */
inline float binterp(float h1, float h2,
                     float h3, float h4,
                     const vec2 & p)
{
    return 0;
}

#endif /*MATH_TYPES_H*/
