#pragma once

#ifndef CONE_H
#define CONE_H

#include <vector>

#include "renderable.h"

struct cone_vertex_t
{
    float x, y, z;
};

typedef unsigned short cone_index_t;

//TODO: Make this draw triangles instead of lines!!!
void draw_cone(const float xoffset, const float yoffset, const float zoffset,
               const float height, const float width);

class Cone: public IRenderable
{
    typedef std::vector<cone_vertex_t>  vertex_array;
    typedef vertex_array::iterator      vertex_iter;
    vertex_array                        vertices;
    static const size_t                 vertex_count(const unsigned int subdivisions);

    typedef std::vector<cone_index_t>   index_array;
    typedef index_array::iterator       index_iter;
    index_array                         indices;
    static const size_t                 index_count(const unsigned int subdivisions);
public:
    Cone(const int subdivisions);
    virtual void render();
};

#endif /*CONE_H*/
