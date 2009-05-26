#pragma once

#ifndef VIEW_H
#define VIEW_H

#include "entity.h"
#include "input_handlers.h"
#include "mouse.h"
#include "camera.h"
#include "entity.h"
#include "renderable.h"

class View: public IKeyboardHandler,
            public IMouseHandler,
            public IRenderState,
            public Entity
{
    bool            mlook;
    Camera          camera;
    Mouse           mouse;
    float           x, y;
    float           elapsed;
public:
    View(unsigned int width, unsigned int height);
    virtual void mouse_down(SDL_MouseButtonEvent & event);
    virtual void mouse_up(SDL_MouseButtonEvent & event);
    virtual void mouse_move(SDL_MouseMotionEvent & event);

    virtual void key_down(SDL_KeyboardEvent & event);
    virtual void key_up(SDL_KeyboardEvent & event);

    virtual void step(const float dtime);

    virtual void begin_render();
    virtual void end_render();
    void set_view();
};

#endif /*VIEW_H*/
