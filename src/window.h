#pragma once

#ifndef VIEWSYSTEM_H
#define VIEWSYSTEM_H

#include <SDL/SDL.h>

class Window
{
    SDL_Surface *   window;
public:
    Window(unsigned int width, unsigned height, const unsigned int bpp, const unsigned int depth, const float clear_color[4], const float clear_depth);
    SDL_Surface * get_surface() {return window;}
    ~Window()
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
};
#endif /*VIEWSYSTEM_H*/
