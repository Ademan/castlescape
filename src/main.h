#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <GL/gl.h>
#include "terrain.h"
#include "terrain_vertex.h"

class Main
{
    SDL_Surface *   window;
public:
    Main(unsigned int width, unsigned int height, int argc, char ** argv);

    void set_view();
    ~Main()
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
private:
    void move(float x, float y);
};

extern Terrain<terrain_vertex_t> *        terrain;

#endif /*MAIN_H*/
