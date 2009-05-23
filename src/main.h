#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <GL/gl.h>
#include "input_handlers.h"
#include "mouse.h"
#include "camera.h"
#include "terrain.h"

#define SENSITIVITY 0.001
#define WIDTH   640
#define HEIGHT  480

class Main: public IMouseHandler, public IKeyboardHandler
{
    Camera          camera;
    Mouse           mouse;
    SDL_Surface *   window;
    bool            mlook;
    float           last;
    float           elapsed;
    float           x, y;
public:
    Main(unsigned int width, unsigned int height);

    virtual void mouse_down(SDL_MouseButtonEvent & event);
    virtual void mouse_up(SDL_MouseButtonEvent & event);
    virtual void mouse_move(SDL_MouseMotionEvent & event);

    virtual void key_down(SDL_KeyboardEvent & event);
    virtual void key_up(SDL_KeyboardEvent & event);

    void set_view();
    void step();
    ~Main()
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
private:
    void move(float x, float y);
};

extern Terrain *        terrain;

#endif /*MAIN_H*/
