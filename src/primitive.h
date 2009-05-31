#pragma once

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

struct cone_vertex_t
{ float x, y, z;
};

inline void draw_compass()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    glEnable(GL_LIGHTING);
}

//TODO: Make this draw triangles instead of lines!!!
inline void draw_cone(const float xoffset, const float yoffset, const float zoffset, const float height, const float width)
{
	glBegin(GL_LINES);
		float top = yoffset + height;
		float a, b, c, d;

		a = xoffset + width;
		b = xoffset - width;
		c = zoffset + width;
		d = zoffset - width;

		glVertex3f(xoffset, top, zoffset);
		glVertex3f(xoffset + width, yoffset, zoffset);

		glVertex3f(xoffset, top, zoffset);
		glVertex3f(xoffset - width, yoffset, zoffset);

		glVertex3f(xoffset, top, zoffset);
		glVertex3f(xoffset, yoffset, zoffset + width);

		glVertex3f(xoffset, top, zoffset);
		glVertex3f(xoffset, yoffset, zoffset - width);

		glVertex3f(a, yoffset, zoffset);
		glVertex3f(b, yoffset, zoffset);

		glVertex3f(a, yoffset, zoffset);
		glVertex3f(xoffset, yoffset, c);

		glVertex3f(a, yoffset, zoffset);
		glVertex3f(xoffset, yoffset, d);
		
		glVertex3f(b, yoffset, zoffset);
		glVertex3f(xoffset, yoffset, c);

		glVertex3f(b, yoffset, zoffset);
		glVertex3f(xoffset, yoffset, d);

		glVertex3f(xoffset, yoffset, c);
		glVertex3f(xoffset, yoffset, d);
	glEnd();
}

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

inline void draw_cube()
{
    glBegin(GL_QUADS);
        z_plane(-0.5, 1);

        z_plane_positive(0.5, 1);

        y_plane_down(-0.5, 1);

        y_plane_up(0.5, 1);

        x_plane(-0.5, 1);

        x_plane_positive(0.5, 1);
    glEnd();
}

#endif
