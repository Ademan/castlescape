#pragma once

#ifndef ARGS_H
#define ARGS_H

//#include <istream>
#include <iostream>
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

template <typename T>
struct factory_t
{
    static void add(Engine & engine, std::istream & stream)
    {
        T * object = constructor_t<T>::construct(std::cin);
        constructor_t<T>::add(engine, object);
    }
};


#endif /*ARGS_H*/
