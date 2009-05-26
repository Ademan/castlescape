#include "terrain_vertex.h"

using cml::normalize;

vec2 norm2(const float height1, const float height2, const float width)
{
    vec2 result;

    float height = height1 - height2;
    float hyp = -sqrt(height * height + width * width);

    result[0] = height / hyp;
    result[1] = width / hyp;

    return result;
}

vec2 norm3(const float height1,
           const float here,
           const float height2,
           const float width)
{

    vec2 left = norm2(height1, here, width);
    vec2 right = norm2(here, height2, width);

    return left + right;
}

//FIXME: !!
vec3 norm_vertex(const float here,
                 const float north, const float south,
                 const float east, const float west,
                 /*const float ne, const float nw,
                 const float se, const float sw,*/
                 const float width)
{
    vec2 vertical = norm3(north, here, south, width);
    vec2 horizontal = norm3(east, here, west, width);

    float hyp = sqrt(2 * width * width);

    /*vec2 up_right = norm3(sw, here, ne, hyp);
    vec2 up_left = norm3(se, here, nw, hyp);*/

    return cml::normalize(vec3(horizontal[0], horizontal[1], 0) +
                          vec3(0, vertical[1], vertical[0]));
}
