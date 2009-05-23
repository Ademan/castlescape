#include <cmath>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include <cml/cml.h>

#include "terrain.h"
#include "math_types.h"
#include "camera.h"
#include "primitive.h"
#include "mouse.h"
#include "aabb.h"
#include "main.h"
#include "input_handlers.h"

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char ** argv)
{
    IMouseHandler * mouse_handler;
    IKeyboardHandler * key_handler;

    Main            main_object(640, 480);
    key_handler =   &main_object;
    mouse_handler = &main_object;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float lava_color[] = {0x90 / 256.0,
                          0x00 / 256.0,
                          0x00 / 256.0,
                          0.5};

    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, lava_color);
    glFogf(GL_FOG_START, 80);
    glFogf(GL_FOG_END, 200);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    glClearColor(lava_color[0], lava_color[1], lava_color[2], 1);
    glClearDepth(1.0);

    SDL_Event   event;

    //unsigned int last = SDL_GetTicks();

	SDL_ShowCursor(SDL_DISABLE);

    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        main_object.step();

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_KEYDOWN:
                key_handler->key_down(event.key);
                break;
            case SDL_KEYUP:
                key_handler->key_up(event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_handler->mouse_down(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_handler->mouse_up(event.button);
                break;
            case SDL_MOUSEMOTION:
                mouse_handler->mouse_move(event.motion);
                break;
            case SDL_QUIT:
                return 0;

            default: break;
            }

        main_object.set_view();
        terrain->render();
#ifdef _DEBUG
        draw_compass();
#endif

        SDL_GL_SwapBuffers();
    }
    return 0;
}
