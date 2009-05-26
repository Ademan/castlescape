#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <GL/gl.h>
#include "types.h"

template <typename vertex_t>
struct accessor_t
{
    static float get_x(const vertex_t & v);
    static float get_y(const vertex_t & v);
    static float get_z(const vertex_t & v);

    static float get_nx(const vertex_t & v);
    static float get_ny(const vertex_t & v);
    static float get_nz(const vertex_t & v);
};

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

#endif /*VERTEX_H*/
