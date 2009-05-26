#pragma once

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

struct cone_vertex_t
{
	float x, y, z;
};

inline void draw_compass()
{
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

#endif
