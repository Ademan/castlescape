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

        if (v[0] > max[0]) result[0] = max[0];
        if (v[0] < min[0]) result[0] = min[0];

        if (v[1] > max[1]) result[1] = max[1];
        if (v[1] < min[1]) result[1] = min[1];

        if (v[2] > max[2]) result[2] = max[2];
        if (v[2] < min[2]) result[2] = min[2];

        return result;
    }
    void move(const vec3 & v)
    {
        min += v;
        max += v;
    }
};

bool intersect(const AABB & a, const AABB & b)
{
    if (a.min[0] > b.max[0]) return false;
    if (a.max[0] < b.min[0]) return false;

    if (a.min[1] > b.max[1]) return false;
    if (a.max[1] < b.min[1]) return false;

    if (a.min[2] > b.max[2]) return false;
    if (a.max[2] < b.min[2]) return false;

    return true;
}

void collide(const AABB & stationary, AABB & dynamic)
{
    if (!intersect(stationary, dynamic)) return;

    // X
    if (stationary.max[0] < dynamic.min[0])
        dynamic.move(
                     vec3(stationary.max[0] - dynamic.min[0],
                          0,0)
                    );

    if (stationary.max[0] < dynamic.min[0])
        dynamic.move(
                     vec3(stationary.max[0] - dynamic.min[0],
                          0,0)
                    );


    // maybe we've resolved the intersection
    if (!intersect(stationary, dynamic)) return;

    // Y
    if (stationary.max[1] < dynamic.min[1])
        dynamic.move(
                     vec3(stationary.max[1] - dynamic.min[1],
                          0,0)
                    );

    if (stationary.max[1] < dynamic.min[1])
        dynamic.move(
                     vec3(stationary.max[1] - dynamic.min[1],
                          0,0)
                    );

    // maybe we've resolved the intersection
    if (!intersect(stationary, dynamic)) return;

    // Z
    if (stationary.max[2] < dynamic.min[2])
        dynamic.move(
                     vec3(stationary.max[2] - dynamic.min[2],
                          0,0)
                    );

    if (stationary.max[2] < dynamic.min[2])
        dynamic.move(
                     vec3(stationary.max[2] - dynamic.min[2],
                          0,0)
                    );
}

#endif /*AABB_H*/
