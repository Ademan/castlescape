#pragma once

#ifndef CASTLE_H
#define CASTLE_H

#include <vector>
#include "renderable.h"
#include "transform.h"

typedef transscale_t castle_transform;

struct cube_with_battlements
{
    std::vector <castle_transform>  battlements;
    castle_transform                transform;

    void generate_corners(castle_transform & battlement,
                          float hwidth);
    void generate_battlement(castle_transform & battlement, float x, float y);
    void generate_battlements();
    void draw_battlements();
};

class Castle: public IRenderable
{
    Castle * keep;
    cube_with_battlements body;
    void generate();
    void generate_as_child();
public:
    Castle();
    Castle(const unsigned int remaining_depth);
    virtual void render();
    ~Castle();
};

#endif /*CASTLE_H*/
