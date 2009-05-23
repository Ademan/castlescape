#pragma once

#ifndef AABB_H
#define AABB_H

#include <limits>
#include "math_types.h"

using std::numeric_limits;
typedef numeric_limits<float> float_limit;

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

template <typename vertex_type>
struct accessor_t
{
    static float get_x(const vertex_type & v);
    static float get_y(const vertex_type & v);
    static float get_z(const vertex_type & v);
};

template <typename vertex_type>
void smallest_AABB(AABB & box, const vertex_type * vertices,
                   const size_t count)
{
    // initialize min to highest
    // possible float value
    // so that any vertex at all
    // will replace it
    for (int i = 0; i < 3; i++)
        box.min[i] = float_limit::max();

    //initialize max to lowest
    //possible values, same idea as above
    for (int i = 0; i < 3; i++)
        box.max[i] = -float_limit::max();

    for (vertex_type * i = vertices; i != vertices + count; i++)
    {
        float x = accessor_t<vertex_type>::get_x(*i);
        float y = accessor_t<vertex_type>::get_y(*i);
        float z = accessor_t<vertex_type>::get_z(*i);

        if (x < box.min[0]) box.min[0] = x;
        else if (x > box.max[0]) box.max[0] = x;

        if (y < box.min[1]) box.min[1] = y;
        else if (y > box.max[1]) box.max[1] = y;

        if (z < box.min[2]) box.min[2] = z;
        else if (z > box.max[2]) box.max[2] = z;
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
                     vec3(0,
                          stationary.max[1] - dynamic.min[1],
                          0)
                    );

    if (stationary.max[1] < dynamic.min[1])
        dynamic.move(
                     vec3(0,
                          stationary.max[1] - dynamic.min[1],
                          0)
                    );

    // maybe we've resolved the intersection
    if (!intersect(stationary, dynamic)) return;

    // Z
    if (stationary.max[2] < dynamic.min[2])
        dynamic.move(
                     vec3(0, 0,
                          stationary.max[2] - dynamic.min[2])
                    );

    if (stationary.max[2] < dynamic.min[2])
        dynamic.move(
                     vec3(0, 0,
                          stationary.max[2] - dynamic.min[2])
                    );
}

#endif /*AABB_H*/
