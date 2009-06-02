#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <string>

#include <GL/gl.h>

#include "types.h"
#include "renderable.h"
#include "entity.h"

#include "args.h"

using std::cout; using std::endl;

inline void enable_lighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
}

inline const GLuint gl_index(unsigned int index) {return GL_LIGHT0 + index;}

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

unsigned int next_light();

class Light: public IRenderState
{
protected:
    light_t light;
    unsigned int index;
public:
    virtual void begin_render();
    virtual void end_render();
};

class OrbitingLight: public Light, public Entity
{
public:
    enum Axis
    {
        XY,
        XZ,
        ZY
    };
protected:
    Axis    axis;
    float   time;
    float   radius;
public:
    OrbitingLight() {}
    OrbitingLight(const Axis _axis, const float _radius, float r, float g, float b): radius(_radius), time(0), axis(_axis)
    {
        light.diffuse[0] = r;
        light.diffuse[1] = g;
        light.diffuse[2] = b;
        light.diffuse[3] = 1.0;
    }
    virtual void step(const float dtime);   
};

class RenderableOrbitingLight: public OrbitingLight, public IRenderable
{
public:
    RenderableOrbitingLight() {}
    RenderableOrbitingLight(const OrbitingLight::Axis _axis, const float _radius, float r, float g, float b): OrbitingLight(_axis, _radius, r, g, b)
       // axis(_axis), radius(_radius), time(0)
    {
        light.diffuse[0] = r;
        light.diffuse[1] = g;
        light.diffuse[2] = b;
        light.diffuse[3] = 1.0;
    }

	//virtual void step(const float dtime);   
	virtual void render();
};

#endif /*LIGHT_H*/
