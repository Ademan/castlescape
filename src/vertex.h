#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cmath>
#include <cassert>
#include <GL/gl.h>

#include <cml/cml.h>
#include "types.h"

using std::cout;
using std::endl;

template <typename vertex_t>
struct accessor_t
{
    static float get_x(const vertex_t & v);
    static float get_y(const vertex_t & v);
    static float get_z(const vertex_t & v);

    static float set_x(vertex_t & v, const float x);
    static float set_y(vertex_t & v, const float y);
    static float set_z(vertex_t & v, const float z);

    static float get_nx(const vertex_t & v);
    static float get_ny(const vertex_t & v);
    static float get_nz(const vertex_t & v);

    static void set_nx(vertex_t & v, const float nx);
    static void set_ny(vertex_t & v, const float ny);
    static void set_nz(vertex_t & v, const float nz);
};

template <typename vertex_t>
const vec3 get_position(const vertex_t & v)
{
    return vec3(accessor_t<vertex_t>::get_x(v),
                accessor_t<vertex_t>::get_y(v),
                accessor_t<vertex_t>::get_z(v));
}

template <typename vertex_t>
void set_position(vertex_t & v, const vec3 & p)
{
    accessor_t<vertex_t>::set_x(v, p[0]);
    accessor_t<vertex_t>::set_y(v, p[1]);
    accessor_t<vertex_t>::set_z(v, p[2]);
}

template <typename vertex_t>
const vec3 get_normal(const vertex_t & v)
{
    return vec3(accessor_t<vertex_t>::get_nx(v),
                accessor_t<vertex_t>::get_ny(v),
                accessor_t<vertex_t>::get_nz(v));
}

template <typename vertex_t>
void set_normal(vertex_t & v, const vec3 & n)
{
    accessor_t<vertex_t>::set_nx(v, n[0]);
    accessor_t<vertex_t>::set_ny(v, n[1]);
    accessor_t<vertex_t>::set_nz(v, n[2]);
}

template <typename vertex_t, typename index_t>
void show_wireframe(const vertex_t * vertices, const size_t vcount, index_t * indices, const size_t icount)
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	
	for (int i = 0; i < icount; i += 3)
	{
		glVertex3f(accessor_t<vertex_t>::get_x(vertices[indices[i]]),
				   accessor_t<vertex_t>::get_y(vertices[indices[i]]),
				   accessor_t<vertex_t>::get_z(vertices[indices[i]]));
		
		glVertex3f(accessor_t<vertex_t>::get_x(vertices[indices[i + 1]]),
				   accessor_t<vertex_t>::get_y(vertices[indices[i + 1]]),
				   accessor_t<vertex_t>::get_z(vertices[indices[i + 1]]));
		
		glVertex3f(accessor_t<vertex_t>::get_x(vertices[indices[i + 1]]),
				   accessor_t<vertex_t>::get_y(vertices[indices[i + 1]]),
				   accessor_t<vertex_t>::get_z(vertices[indices[i + 1]]));

		glVertex3f(accessor_t<vertex_t>::get_x(vertices[indices[i + 2]]),
				   accessor_t<vertex_t>::get_y(vertices[indices[i + 2]]),
				   accessor_t<vertex_t>::get_z(vertices[indices[i + 2]]));
		
		glVertex3f(accessor_t<vertex_t>::get_x(vertices[indices[i]]),
				   accessor_t<vertex_t>::get_y(vertices[indices[i]]),
				   accessor_t<vertex_t>::get_z(vertices[indices[i]]));
		
		glVertex3f(accessor_t<vertex_t>::get_x(vertices[indices[i + 2]]),
				   accessor_t<vertex_t>::get_y(vertices[indices[i + 2]]),
				   accessor_t<vertex_t>::get_z(vertices[indices[i + 2]]));
	}

	glEnd();
}

template <typename vertex_t>
void show_normals(const vertex_t * vertices, const size_t count)
{
    glColor3f(1, 0, 1);
    glBegin(GL_LINES);
    for (const vertex_t * i = vertices; i != vertices + count; i++)
    {
        glVertex3f(accessor_t<vertex_t>::get_x(*i),
                   accessor_t<vertex_t>::get_y(*i),
                   accessor_t<vertex_t>::get_z(*i));

        glVertex3f(accessor_t<vertex_t>::get_x(*i) +
                   accessor_t<vertex_t>::get_nx(*i),

                   accessor_t<vertex_t>::get_y(*i) +
                   accessor_t<vertex_t>::get_ny(*i),

                   accessor_t<vertex_t>::get_z(*i) +
                   accessor_t<vertex_t>::get_nz(*i)
                   );
    }
    glEnd();
}

template <typename vertex_t>
vec3 triangle_normal(const vertex_t & a, const vertex_t & b, const vertex_t & c)
{
    vec3 va = get_position(a);
    vec3 vb = get_position(b);
    vec3 vc = get_position(c);

    vec3 x = va - vb;
    vec3 y = vc - vb;

    return cml::unit_cross(y, x);
}

template <typename vertex_t>
void set_triangle_normal(vertex_t & a, vertex_t & b, vertex_t & c)
{
    vec3 normal = triangle_normal(a, b, c);

    set_normal(a, get_normal(a) + normal);
    set_normal(b, get_normal(b) + normal);
    set_normal(c, get_normal(c) + normal);
}

template <typename vertex_t, typename index_t, const unsigned int type>
void generate_normals(vertex_t * vertices, const size_t vertex_count,
                      const index_t * indices, const size_t index_count)
{
    if (type != GL_TRIANGLES) assert("other types not implemented");

    assert (index_count % 3 == 0);
    
    for (int i = 0; i < index_count;)
        set_triangle_normal(vertices[indices[i++]], vertices[indices[i++]], vertices[indices[i++]]);

    for (int i = 0; i < vertex_count; i++)
    {
        set_normal(vertices[i], cml::normalize(get_normal(vertices[i])));
    }
}

#endif /*VERTEX_H*/
