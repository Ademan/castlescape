#pragma once

#ifndef CASTLE_H
#define CASTLE_H

#include <vector>
#include "renderable.h"
#include "transform.h"

typedef transform_t <euler_rotation_t> castle_transform;

struct cube_with_battlements
{
    std::vector <castle_transform>  battlements;
    castle_transform                body;
    void generate_corners(float bwidth);
    void generate_battlements();
    void draw();
};

class Castle: public IRenderable
{
    cube_with_battlements keep;
    cube_with_battlements body;
public:
    Castle();
    virtual void render();
};

#endif /*CASTLE_H*/
