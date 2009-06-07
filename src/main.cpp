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
#include "input_handlers.h"
#include "timer.h"
#include "engine.h"
#include "view.h"
#include "light.h"
#include "window.h"
#include "args.h"
#include "castle.h"
#include "lua_manager.h"

using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
    srand(time(NULL));
    Engine          engine;
    Timer           timer;
    View            view(640, 480);
    Castle          castles[5];
    //OrbitingLight   light(64, 1, 0, 0);
    //RenderableOrbitingLight light2(64, 1, 1, 0);
	//FIXME: Move this into the engine.
	doLua();

    float lava_color[] = {0x90 / 256.0,
                          0x00 / 256.0,
                          0x00 / 256.0,
                          0.5};

    Window            window(640, 480, 24, 16, lava_color, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ((float)640)/480, 1.0, 1000.0);
 
    /*Terrain<terrain_vertex_t> terrain(argv[1]);
    cout << "Vertices: " << terrain.get_vertex_count() << endl;
    cout << "Indices: " << terrain.get_index_count() << endl;*/

	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glFrontFace(GL_CW);
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, lava_color);
    glFogf(GL_FOG_START, 32);
    glFogf(GL_FOG_END, 64);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    SDL_Event   event;

	SDL_ShowCursor(SDL_DISABLE);

    engine.add_keyboard_handler(&view);
    engine.add_mouse_handler(&view);
    engine.add_entity(&view);
    engine.add_render_state(&view);

    enable_lighting();

    //FIXME: remove once lua integration is mature
    construct(engine);

    for (unsigned int i = 0; i < 5; i++)
        engine.add_renderable(castles + i);

    //FIXME: remove me later
    Cone cone(16);
    engine.add_renderable(&cone);

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
        engine.render();
        engine.end_render();
#ifdef _DEBUG
        draw_compass();
#endif

        SDL_GL_SwapBuffers();
    }
    return 0;
}
