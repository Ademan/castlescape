#include <iostream>
#include <GL/glu.h>

#include "main.h"
#include "util.h"

using std::cout;
using std::cerr;
using std::endl;

#define MOVESPEED 25

Main::Main(unsigned int width, unsigned int height):
     mouse(&camera, width, height, SENSITIVITY),
     mlook(true), x(0), y(0)
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    window = SDL_SetVideoMode(width, height, 24, SDL_OPENGL);

    if (!window)
    {
        cout << "Failed to create window!!" << endl;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ((float)width)/height, 1.0, 1000.0);
    terrain = new Terrain <terrain_vertex_t>("media/height.png");
}

void Main::mouse_down(SDL_MouseButtonEvent & event)
{
    
}

void Main::mouse_up(SDL_MouseButtonEvent & event)
{

}

void Main::mouse_move(SDL_MouseMotionEvent & event)
{
    if (!mlook)
        if (event.state & SDL_BUTTON(1))
        {
            mouse.dragcamera(event.xrel / 200.0,
                          event.yrel / 200.0);
        }
}


void Main::key_down(SDL_KeyboardEvent & event)
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

void Main::key_up(SDL_KeyboardEvent & event)
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

void Main::set_view()
{
    move(x, y);
    //TODO: wat?
    if (mlook)
        mouse.update();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(camera.get_mat().data());
}

void Main::step()
{
    unsigned int now = SDL_GetTicks();

    elapsed = (now - last) / 1000.0f;
    last = now;
}

void Main::move(float x, float y)
{
        camera.move(vec3(x * elapsed * MOVESPEED, 0, y * elapsed * MOVESPEED));
        //camera.collide();
        vec3 newpos = terrain->get_aabb().clamp(camera.get_pos());
        camera.set_pos(newpos);
}

Terrain<terrain_vertex_t> * terrain;
