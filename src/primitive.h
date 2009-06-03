#pragma once

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "cone.h"
#include "cylinder.h"

void draw_compass();

//FIXME: rename plane functions to be sane!
void draw_cube();

inline void y_plane_up(const float y, const float width)
{
        glNormal3f(0, 1, 0);
    glVertex3f(width / -2.0, y, width / -2.0);
        glNormal3f(0, 1, 0);
    glVertex3f(width / 2.0, y, width / -2.0);
        glNormal3f(0, 1, 0);
    glVertex3f(width / 2.0, y, width / 2.0);
        glNormal3f(0, 1, 0);
    glVertex3f(width / -2.0, y, width / 2.0);
}

inline void y_plane_down(const float y, const float width)
{
        glNormal3f(0, -1, 0);
    glVertex3f(width / -2.0, y, width / -2.0);
        glNormal3f(0, -1, 0);
    glVertex3f(width / -2.0, y, width / 2.0);
        glNormal3f(0, -1, 0);
    glVertex3f(width / 2.0, y, width / 2.0);
        glNormal3f(0, -1, 0);
    glVertex3f(width / 2.0, y, width / -2.0);
}

inline void x_plane(const float x, const float width)
{
        glNormal3f(-1, 0, 0);
    glVertex3f(x, width / -2.0, width / -2.0);
        glNormal3f(-1, 0, 0);
    glVertex3f(x, width / 2.0, width / -2.0);
        glNormal3f(-1, 0, 0);
    glVertex3f(x, width / 2.0, width / 2.0);
        glNormal3f(-1, 0, 0);
    glVertex3f(x, width / -2.0, width / 2.0);
}

inline void x_plane_positive(const float x, const float width)
{
        glNormal3f(1, 0, 0);
    glVertex3f(x, width / 2.0, width / -2.0);
        glNormal3f(1, 0, 0);
    glVertex3f(x, width / -2.0, width / -2.0);
        glNormal3f(1, 0, 0);
    glVertex3f(x, width / -2.0, width / 2.0);
        glNormal3f(1, 0, 0);
    glVertex3f(x, width / 2.0, width / 2.0);
}

inline void z_plane(const float z, const float width)
{
        glNormal3f(0, 0, -1);
    glVertex3f(width / -2.0, width / -2.0, z);
        glNormal3f(0, 0, -1);
    glVertex3f(width / 2.0, width / -2.0, z);
        glNormal3f(0, 0, -1);
    glVertex3f(width / 2.0, width / 2.0, z);
        glNormal3f(0, 0, -1);
    glVertex3f(width / -2.0, width / 2.0, z);
}

inline void z_plane_positive(const float z, const float width)
{
        glNormal3f(0, 0, 1);
    glVertex3f(width / 2.0, width / -2.0, z);
        glNormal3f(0, 0, 1);
    glVertex3f(width / -2.0, width / -2.0, z);
        glNormal3f(0, 0, 1);
    glVertex3f(width / -2.0, width / 2.0, z);
        glNormal3f(0, 0, 1);
    glVertex3f(width / 2.0, width / 2.0, z);
}

#endif
