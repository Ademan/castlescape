#include <iostream>
#include <GL/gl.h>

#include "view.h"
#include "util.h"

using std::cout;
using std::endl;

#define MOVESPEED 25
#define SENSITIVITY 0.001

View::View(unsigned int width, unsigned int height): mlook(true), mouse(&camera, width, height, SENSITIVITY), x(0), y(0) {

	vec3 cpos(0, 25, 0);
	camera.set_pos(cpos);
}

void View::mouse_down(SDL_MouseButtonEvent & event)
{
    
}

void View::mouse_up(SDL_MouseButtonEvent & event)
{

}

void View::mouse_move(SDL_MouseMotionEvent & event)
{
    if (!mlook)
        if (event.state & SDL_BUTTON(1))
        {
            mouse.dragcamera(event.xrel / 200.0,
                          event.yrel / 200.0);
        }
}

void View::key_down(SDL_KeyboardEvent & event)
{
    switch (event.keysym.sym)
    {
    case SDLK_w:
        y += 1;
        break;
    case SDLK_s:
        y -= 1;
        break;
    case SDLK_a:
        x += 1;
        break;
    case SDLK_d:
        x -= 1;
        break;
    default: break;
    }
}

void View::key_up(SDL_KeyboardEvent & event)
{
    switch (event.keysym.sym)
    {
    case SDLK_w:
        y -= 1;
        break;
    case SDLK_s:
        y += 1;
        break;
    case SDLK_a:
        x -= 1;
        break;
    case SDLK_d:
        x += 1;
        break;
    case SDLK_q:
        send_quit(0);
        break;
    case SDLK_l:
        mlook = !mlook;
        if (!mlook)
            SDL_ShowCursor(SDL_ENABLE);
        else
            SDL_ShowCursor(SDL_DISABLE);
    default: break;
    }
}

void View::set_view()
{
    if (mlook)
        mouse.update();

    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glLoadMatrixf(camera.get_mat().data());
}


void View::step(const float dtime)
{
    //FIXME!!!!
    elapsed = dtime;
    //x = y = 0;
}

void View::begin_render()
{
    camera.move(vec3(x * elapsed * MOVESPEED, 0, y * elapsed * MOVESPEED));
    set_view();
}

void View::end_render()
{

}
