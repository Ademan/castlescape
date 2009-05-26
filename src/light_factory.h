#pragma once

#ifndef LIGHT_FACTORY_H
#define LIGHT_FACTORY_H

#include "light.h"

template <>
struct constructor_t<OrbitingLight>
{
    static const char * name() {return "orbit_light";}
    static OrbitingLight * construct(std::istream & stream)
    {
        std::string axis;
        stream >> axis;

        OrbitingLight::Axis a;

        if (axis == "xy")
         a = OrbitingLight::XY;
        else if (axis == "xz")
         a = OrbitingLight::XZ;   
        else
         a = OrbitingLight::ZY;

        float radius;
        float r, g, b;

        stream >> radius;
        stream >> r >> g >> b;

        //FIXME: introduces sweet memory leak
        return new OrbitingLight(a, radius, r, g, b);
    }
    static void add(Engine & engine, OrbitingLight * light)
    {
        engine.add_entity(light);
        engine.add_render_state(light);
    }
};

#endif /*LIGHT_FACTORY_H*/
