#pragma once

#ifndef TERRAIN_VERTEX_H
#define TERRAIN_VERTEX_H

#include <GL/gl.h>

#include "terrain_templates.h"
#include "vertex.h"
#include "types.h"

template <typename T>
const T clamp(const T min, const T max, const T val)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

template <typename index_t>
struct clamping_indexer_t
{
    size_t width;
    size_t height;
    clamping_indexer_t(const size_t _width, const size_t _height): width(_width), height(_height) {}
    const index_t operator () (const int x, const int y)
    {
        return clamp(0, static_cast <int> (width), x)
            + (clamp(0, static_cast <int> (height), y) * width);
    }
};

struct terrain_vertex_t
{
    float x, y, z;
    float r, g, b;
    //float s, t; /*texture coordinates*/
    float nx, ny, nz; /*normal coordinates*/
};

vec3 norm_vertex(const float here,
                 const float north, const float south,
                 const float east, const float west,
                 const float width);

//FIXME:!!
//make index type agnostic
template <>
struct vertex_processor<terrain_vertex_t, unsigned int>
{
    static void generate(terrain_vertex_t & v, const int x, const int y,
                         const size_t width, const size_t height,
                         color_t color)
    {
        v.x = x - width / 2.0;
        v.z = y - width / 2.0;

        int red = color[0];

        v.y = red / 16.0;

        v.r = v.g = v.b = red / 256.0;

        if (v.r < 0.1)
        {
            float orig = (v.r + 0.4) * 1.5;

            v.r = 0xff / 256.0;
            v.g = 0x15 / 256.0;
            v.b = 0x00 / 256.0;

            v.r *= orig;
            v.b *= orig;
            v.g *= orig;
        }
        else if (v.r < 0.5)
        {
            float orig = v.r * 1.5;

            v.r = 0x77 / 256.0;
            v.g = 0x4C / 256.0;
            v.b = 0x0f / 256.0;

            v.r *= orig;
            v.b *= orig;
            v.g *= orig;

        }
        else
        {
            float orig = v.r * 1.5;
            v.r = v.g = v.b = orig * 0.5;
        }
    }
    static void postprocess(terrain_vertex_t * vertices,
                            const size_t vertex_count,
                            unsigned int * indices,
                            const size_t index_count)
    {
        generate_normals <terrain_vertex_t, unsigned int, GL_TRIANGLES> (vertices, vertex_count, indices, index_count);
        /*clamping_indexer_t <int> in(width, height);
        float vert_distance = vertices[0].x - vertices[1].x;
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
            {
                vec3 normal = norm_vertex(vertices[in(x, y)].y,
                                          vertices[in(x, y + 1)].y, //north
                                          vertices[in(x, y - 1)].y, //south
                                          vertices[in(x + 1, y)].y, //east
                                          vertices[in(x - 1, y)].y, //west
                                          vert_distance);

                vertices[in(x, y)].nx = normal[0];
                vertices[in(x, y)].ny = normal[1];
                vertices[in(x, y)].nz = normal[2];
            }*/
    }
    static void prepare()
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
    }
    static void submit(terrain_vertex_t * vertices)
    {
        glVertexPointer(3, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->x));
        glColorPointer(3, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->r));
		glNormalPointer(GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->nx));
    }
    static void done()
    {
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};

template<>
struct accessor_t<terrain_vertex_t>
{
    static float get_x(const terrain_vertex_t & v) {return v.x;}
    static float get_y(const terrain_vertex_t & v) {return v.y;}
    static float get_z(const terrain_vertex_t & v) {return v.z;}

    static void set_x(terrain_vertex_t & v, const float x) {v.x = x;}
    static void set_y(terrain_vertex_t & v, const float y) {v.y = y;}
    static void set_z(terrain_vertex_t & v, const float z) {v.z = z;}

    static float get_r(const terrain_vertex_t & v) {return v.r;}
    static float get_g(const terrain_vertex_t & v) {return v.g;}
    static float get_b(const terrain_vertex_t & v) {return v.b;}

    static float get_nx(const terrain_vertex_t & v) {return v.nx;}
    static float get_ny(const terrain_vertex_t & v) {return v.ny;}
    static float get_nz(const terrain_vertex_t & v) {return v.nz;}

    static void set_nx(terrain_vertex_t & v, const float nx) {v.nx = nx;}
    static void set_ny(terrain_vertex_t & v, const float ny) {v.ny = ny;}
    static void set_nz(terrain_vertex_t & v, const float nz) {v.nz = nz;}
};

#endif /*TERRAIN_VERTEX_H*/
