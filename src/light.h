#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>

#include <GL/gl.h>

#include "types.h"
#include "renderable.h"
#include "entity.h"

using std::cout;
using std::endl;

inline void enable_lighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
}

struct light_t
{
    vec3    pos;
    enum LightType
    {
        Point,
        Spot,
        Directional
    }type;
    float  ambient[4];
    float  diffuse[4];
    float  specular[4];
    //float  emission[4];
    const GLuint gl_index(GLuint index) const {return GL_LIGHT0 + index;}
    light_t()
    {
        for (int i = 0; i < 4; i++)
        {
            ambient[i] = 0;
            diffuse[i] = 0;
            specular[i] = 0;
        }
    }
    void dump()
    {
        cout << "ambient: ";
        for (int i = 0; i < 4; i++)
            cout << ' ' << ambient[i];

        cout << endl << "diffuse:";
        for (int i = 0; i < 4; i++)
            cout << ' ' << diffuse[i];

        cout << endl << "specular:";
        for (int i = 0; i < 4; i++)
            cout << ' ' << specular[i];
        cout << endl;
    }
    void enable(GLuint index)
    {
        glEnable(gl_index(index));

        GLfloat position[] = {pos[0],
                              pos[1],
                              pos[2],
                              0.0};

        if (type == Point)
        {
            position[3] = 1;
        }

        glLightfv(gl_index(index),
                  GL_POSITION,
                  position);

        //glEnable(GL_COLOR_MATERIAL);
        glLightfv(gl_index(index), GL_AMBIENT, ambient);
        glLightfv(gl_index(index), GL_DIFFUSE, diffuse);
        glLightfv(gl_index(index), GL_SPECULAR, specular);
        //glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }
    void disable(const GLuint index)
    {
        glDisable(gl_index(index));
    }
};

class Light: public IRenderState
{
protected:
    light_t light;
public:
    virtual void begin_render();
    virtual void end_render();
};

class OrbitingLight: public Light, public Entity
{
protected:
    float   time;
    float   radius;
public:
    OrbitingLight(const float _radius): radius(_radius), time(0)
    {
        light.diffuse[0] = 1.0;
        light.diffuse[3] = 1.0;
    }
    virtual void step(const float dtime);   
};

class RenderableOrbitingLight: public Light, public Entity, public IRenderable
{
protected:
	float   time;
    float   radius;
public:
    RenderableOrbitingLight(const float _radius): radius(_radius), time(0)
    {
        light.diffuse[0] = 1.0;
        light.diffuse[3] = 1.0;
    }
 
	virtual void step(const float dtime);   
	virtual void render();
};

#endif /*LIGHT_H*/
