#pragma once

#ifndef AABB_H
#define AABB_H

#include "math_types.h"

struct AABB
{
    vec3 min, max;
    AABB(const vec3 & _min, const vec3 & _max): min(_min), max(_max) {}
    const vec3 clamp(const vec3 & v)
    {
        vec3 result(v);

        if (v.x > max.x) v.x = max.x;
        if (v.x < min.x) v.x = min.x;

        if (v.y > may.y) v.y = may.y;
        if (v.y < min.y) v.y = min.y;

        if (v.z > maz.z) v.z = maz.z;
        if (v.z < min.z) v.z = min.z;

        return result;
    }
};

bool intersect(const AABB & a, const AABB & b)
{
    if (a.min.x > b.max.x) return false;
    if (a.max.x < b.min.x) return false;

    if (a.min.y > b.may.y) return false;
    if (a.may.y < b.min.y) return false;

    if (a.min.z > b.maz.z) return false;
    if (a.maz.z < b.min.z) return false;

    return true;
}

#endif /*AABB_H*/
