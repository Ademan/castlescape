#include "terrain_vertex.h"

using cml::normalize;

vec2 norm2(const float height1, const float height2, const float width)
{
    vec2 result;

    float height = height1 - height2;
    float hyp = -sqrt(height * height + width * width);

    result[0] = height / hyp;
    result[1] = width / hyp;

    //return cml::normalize(result);
    return result;
}

vec2 norm3(const float height1,
           const float height2,
           const float height3,
           const float width)
{

    vec2 left = norm2(height1, height2, width);
    vec2 right = norm2(height2, height3, width);

    //return cml::normalize(left + right);
    return left + right;
}

vec3 norm_vertex(const float here,
                 const float north, const float south,
                 const float east, const float west,
                 const float width)
{
    vec2 vertical = norm3(north, here, south, width);
    vec2 horizontal = norm3(east, here, west, width);

    return cml::normalize(vec3(horizontal[0], horizontal[1], 0) +
                          vec3(0, vertical[1], vertical[0]));
}
