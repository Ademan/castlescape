#pragma once

#ifndef TERRAIN_VERTEX_H
#define TERRAIN_VERTEX_H

#include <iostream>
#include <GL/gl.h>

#include "terrain_templates.h"
#include "vertex.h"
#include "types.h"

template <typename T>
struct v_color
{
	T r, g, b;
	v_color() {}
	v_color(const v_color & n): r(n.r), g(n.g), b(n.b) {}
	v_color(const T _r, const T _g, const T _b): r(_r), g(_g), b(_b) {}
	const v_color adjust() { return v_color(r / 255.0, g / 255.0, b / 255.0); }
	const v_color operator- (const v_color & rhs) const { return v_color(r - rhs.r, g - rhs.g, b - rhs.b); } 
	const v_color correct()
	{
		float nr, ng, nb;
		if (r < 0) nr = 0;
		if (r > 1) nr = 1;
		if (g < 0) ng = 0;
		if (g > 1) ng = 1;
		if (b < 0) nb = 0;
		if (b > 1) nb = 1;
		return v_color(nr, ng, nb);
	}
};

typedef v_color<float> v_colorf;

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
    float s, t; /*texture coordinates*/
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
	static float highest(const terrain_vertex_t * vertices, const size_t vertex_count)
	{
		float highest = -999999999.0f;
		for (int i = 0; i < vertex_count; i++)
			if (vertices[i].y > highest)
				highest = vertices[i].y;

		return highest;
	}

    static void generate(terrain_vertex_t & v, const int x, const int y,
                         const size_t width, const size_t height,
                         color_t color)
    {
        v.x = x - width / 2.0;
        v.z = y - width / 2.0;

        int red = color[0];
        v.y = red / 16.0;
        v.r = v.g = v.b = red / 255.0;
        v.s = x;
        v.t = y;
	}

	static void color_vertex(terrain_vertex_t & v, const float highest,
							 const v_colorf * colors, const float * v_heights, 
							 const size_t color_count)
	{
		v_colorf orig((v.r + 0.4) * 1.5, (v.g + 0.4) * 1.5, (v.b + 0.4) * 1.5);
		float percentage = v.y / highest; 
		for (int i = 0; i < color_count - 1; i++)
		{
			v_colorf grade = colors[i] - colors[i + 1];
			if (percentage <= v_heights[i])
			{
				float grade_percent = percentage * (v_heights[i+1] - v_heights[i]);
				v.r = colors[i].r + ((grade.r) * (grade_percent));
				v.g = colors[i].g + ((grade.g) * (grade_percent));
				v.b = colors[i].b + ((grade.b) * (grade_percent));
				break;
			}
			else
				v.r = colors[color_count - 1].r;
				v.g = colors[color_count - 1].g;
				v.b = colors[color_count - 1].b;
		}
		v.r *= orig.r;
		v.g *= orig.g;
		v.b *= orig.b;
	}
      
    static void postprocess(terrain_vertex_t * vertices,
                            const size_t vertex_count,
                            unsigned int * indices,
                            const size_t index_count)
    {
        generate_normals <terrain_vertex_t, unsigned int, GL_TRIANGLES> (vertices, vertex_count, indices, index_count);

		/*v_colorf low(0xff, 0x15, 0x00); //orangy red
		v_colorf med(0x77, 0x4c, 0x0f); //brown
		v_colorf high(0xee, 0xee, 0xee); //gray
		v_colorf colors[] = {v_colorf(low.adjust()), v_colorf(med.adjust()), v_colorf(high.adjust())};
		float heights[] = {.1, .5, .95};*/

		v_colorf red(0xff, 0x00, 0x00);
		v_colorf orange(0xff, 0x7f, 0x00);
		v_colorf yellow(0xff, 0xff, 0x00);
		v_colorf green(0x00, 0xff, 0x00);
		v_colorf blue(0x00, 0x00, 0xff);
		v_colorf purple(0xff, 0x00, 0xff);

		float heights[] = {.166, .333, .5, .666, .833, 2.0};
		v_colorf colors[] = {v_colorf(red.adjust()), v_colorf(orange.adjust()), v_colorf(yellow.adjust()),
							 v_colorf(green.adjust()), v_colorf(blue.adjust()), v_colorf(purple.adjust())};

		float high_v = highest(vertices, vertex_count);
		
		/*for (int i = 0; i < vertex_count; i++)
			color_vertex(vertices[i], high_v, colors, heights, 6);*/

        /*clamping_indexer_t <int> in(width, height);
		 *
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
        //glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    static void submit(terrain_vertex_t * vertices)
    {
        glVertexPointer(3, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->x));
        //glColorPointer(3, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->r));
        glTexCoordPointer(2, GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->s));
		glNormalPointer(GL_FLOAT, sizeof(terrain_vertex_t), &(vertices->nx));
    }
    static void done()
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
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
