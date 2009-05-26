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
#include "timer.h"
#include "engine.h"
#include "view.h"
#include "light.h"

using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
    Engine          engine;
    Timer           timer;
    View            view(640, 480);
    OrbitingLight   light(64);

    Main            main_object(640, 480, argc, argv);

	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float lava_color[] = {0x90 / 256.0,
                          0x00 / 256.0,
                          0x00 / 256.0,
                          0.5};
	glFrontFace(GL_CW);
    //glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, lava_color);
    glFogf(GL_FOG_START, 80);
    glFogf(GL_FOG_END, 200);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    glClearColor(lava_color[0], lava_color[1], lava_color[2], 1);
    glClearDepth(1.0);

    SDL_Event   event;

	SDL_ShowCursor(SDL_DISABLE);

    engine.add_keyboard_handler(&view);
    engine.add_mouse_handler(&view);
    engine.add_entity(&view);
    engine.add_render_state(&view);

    enable_lighting();
    engine.add_render_state(&light);
    engine.add_entity(&light);

    timer.elapsed();
    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        engine.step(timer.elapsed());

        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_KEYDOWN:
                engine.key_down(event.key);
                break;
            case SDL_KEYUP:
                engine.key_up(event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                engine.mouse_down(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                engine.mouse_up(event.button);
                break;
            case SDL_MOUSEMOTION:
                engine.mouse_move(event.motion);
                break;
            case SDL_QUIT:
                return 0;

            default: break;
            }

        engine.begin_render();
        terrain->render();
        engine.render();
        engine.end_render();
#ifdef _DEBUG
        draw_compass();
#endif

        SDL_GL_SwapBuffers();
    }
    return 0;
}
