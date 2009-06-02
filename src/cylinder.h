#pragma once

#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include "renderable.h"

struct cylinder_vertex_t
{
    float x, y, z;
    float s, t;
    float nx, ny, nz;
};

typedef unsigned short cylinder_index_t;

class Cylinder: public IRenderable
{
    typedef std::vector <cylinder_vertex_t> vertex_array;
    typedef vertex_array::iterator          vertex_iter;
    vertex_array vertices;
    static const size_t vertex_count(const unsigned int subdivisons);

    typedef std::vector <cylinder_index_t>  index_array;
    typedef index_array::iterator           index_iter;
    index_array  indices;
    static const size_t index_count(const unsigned int subdivisions);
public:
    Cylinder() {}
    Cylinder(const unsigned int subdivisions);
    virtual void render();
};

#endif /*CYLINDER_H*/
