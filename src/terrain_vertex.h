#pragma once

#ifndef TERRAIN_VERTEX_H
#define TERRAIN_VERTEX_H

#include "terrain_templates.h"
#include "types.h"

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

template <>
struct vertex_processor<terrain_vertex_t>
{
    static void generate(terrain_vertex_t & v, const int x, const int y,
                         const size_t width, const size_t height,
                         color_t color)
    {
        v.x = x * 2.0 - width;
        v.z = y * 2.0 - height; // "terrain space"s y is world z

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
                            const size_t width, const size_t height)
    {
        for (;;);

    }
    static void prepare()
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
    }
    static void submit(terrain_vertex_t * vertices)
    {
        glVertexPointer(3, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->x));
        glColorPointer(3, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->r));
    }
    static void done()
    {
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};

template<>
struct accessor_t<terrain_vertex_t>
{
    static float get_x(const terrain_vertex_t & v) {return v.x;}
    static float get_y(const terrain_vertex_t & v) {return v.y;}
    static float get_z(const terrain_vertex_t & v) {return v.z;}

    static float get_r(const terrain_vertex_t & v) {return v.r;}
    static float get_g(const terrain_vertex_t & v) {return v.g;}
    static float get_b(const terrain_vertex_t & v) {return v.b;}

    static float get_nx(const terrain_vertex_t & v) {return v.nx;}
    static float get_ny(const terrain_vertex_t & v) {return v.ny;}
    static float get_nz(const terrain_vertex_t & v) {return v.nz;}
};

#endif /*TERRAIN_VERTEX_H*/
