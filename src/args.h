#pragma once

#ifndef ARGS_H
#define ARGS_H

#include <istream>
//#include <type_traits>
#include <string>
#include "engine.h"

void construct(Engine & engine);

template <typename T>
struct constructor_t
{
    static const char * name;
    static T * construct(std::istream & stream);
    static void add(Engine & engine, T * object);
};

//using std::tr1::is_base_of;
//using std::is_base_of;
template <typename T>
struct factory_t
{
    /*(static void add(Engine & engine, T * object)
    {
        if (is_base_of <IRenderable, T>::value)
            engine.add_renderable(object);

        if (is_base_of <Entity, T>::value)
            engine.add_entity(object);

        if (is_base_of <IRenderState, T>::value)
            engine.add_render_state(object);
    }*/
};


#endif /*ARGS_H*/
