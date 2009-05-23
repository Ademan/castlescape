#pragma once

#ifndef INPUT_HANDLERS_H
#define INPUT_HANDLERS_H

#include <SDL/SDL.h>

class IMouseHandler
{
public:
    virtual void mouse_down(SDL_MouseButtonEvent & event) = 0;
    virtual void mouse_up(SDL_MouseButtonEvent & event) = 0;
    virtual void mouse_move(SDL_MouseMotionEvent & event) = 0;
};

class IKeyboardHandler
{
public:
    virtual void key_down(SDL_KeyboardEvent & event) = 0;
    virtual void key_up(SDL_KeyboardEvent & event) = 0;
};

#endif
