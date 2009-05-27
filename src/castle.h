#pragma once

#ifndef CASTLE_H
#define CASTLE_H

#include <vector>
#include "renderable.h"



class Castle: public IRenderable
{
    std::vector <cube_t>  cubes;
public:
    Castle()
    virtual void render();
};

#endif /*CASTLE_H*/
