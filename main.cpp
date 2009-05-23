#include <cmath>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#define WIDTH   640
#define HEIGHT  480

#define MOVESPEED 25

#include <cml/cml.h>
#include "terrain.h"
#include "math_types.h"
#include "camera.h"
#include "primitive.h"

using std::cout;
using std::endl;
using std::ifstream;

using cml::quaternion_rotate_about_local_x;
using cml::quaternion_rotate_about_local_y;

using cml::quaternion_rotate_about_world_x;
using cml::quaternion_rotate_about_world_y;

int cleanup(GLuint texture, SDL_Surface * stex)
{
    glDeleteTextures(1, &texture);
    SDL_FreeSurface(stex);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    return 0;
}


int main(int argc, char ** argv)
{

    if (argc < 2)
    {
        cout << "Need a file!" << endl;
        return 1;
    }

    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    SDL_Surface * window = NULL;
    window = SDL_SetVideoMode(WIDTH, HEIGHT, 24, SDL_OPENGL);

    if (!window)
    {
        cout << "Failed to create window!!" << endl;
        return 1;
    }

    SDL_Surface * stex = NULL;
    stex = IMG_Load(argv[1]);

    Terrain         terrain("height.png");

    GLuint        texture = 0;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    cout << "sending tex" << endl;
    cout << "tex @" << stex << endl;
    cout << " width: " << stex->w << endl;
    cout << " height: " << stex->h << endl;
    glTexImage2D(GL_TEXTURE_2D, 0, /*mipmap level*/
                 GL_RGBA, /*internal format*/
                 stex->w, stex->h,
                 0, /*border*/
                 GL_RGBA, /*data format*/
                 GL_UNSIGNED_BYTE, /*component data*/
                 stex->pixels);
    cout << "done sending tex" << endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*float lava_color[] = {0xff / 256.0,
                          0x15 / 256.0,
                          0x00 / 256.0,
                          0.5};*/

    float lava_color[] = {0x90 / 256.0,
                          0x00 / 256.0,
                          0x00 / 256.0,
                          0.5};

    /*float lava_color[] = {0,
                          0,
                          0,
                          0.5};*/
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, lava_color);
    glFogf(GL_FOG_START, 80);
    glFogf(GL_FOG_END, 200);
    glFogi(GL_FOG_MODE, GL_LINEAR);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ((float)WIDTH)/HEIGHT, 1.0, 1000.0);

    cout << "now" << endl;
    glClearColor(lava_color[0], lava_color[1], lava_color[2], 1);
    cout << "and again" << endl;
    glClearDepth(1.0);

    SDL_Event   event;
    Camera      camera;
    camera.setpos(vec3(0, 0, 10));

    unsigned int last = SDL_GetTicks();
    float x = 0;
    float y = 0;
    cout << "entering main loop" << endl;
    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        unsigned int now = SDL_GetTicks();

        float elapsed = (now - last) / 1000.0f;
        last = now;
        while (SDL_PollEvent(&event))
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
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
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
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
                    return cleanup(texture, stex);
                default: break;
                }
                break;
            case SDL_MOUSEMOTION:
                if (event.motion.state & SDL_BUTTON(1))
                {
                    camera.rotate(event.motion.xrel / 200.0,
                                  event.motion.yrel / 200.0);
                }
                break;
            case SDL_QUIT:
                //cleanup
                return cleanup(texture, stex);

            default: break;
            }

        camera.move(vec3(x *  elapsed * MOVESPEED, 0, y * elapsed * MOVESPEED));
        camera.collide();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glLoadMatrixf(camera.get_mat().data());
        //glTranslatef(0, 0, -10);

#ifndef TERRAIN_H
        glBegin(GL_QUADS);
            glColor3f(0, 0, 1);
            glVertex3f(-9001, -1, -9001);
            glVertex3f(-9001, -1, 9001);
            glVertex3f(9001, -1, 9001);
            glVertex3f(9001, -1, -9001);
        glEnd();
#else
        terrain.render();
        draw_compass();
#endif

        SDL_GL_SwapBuffers();
    }
    return 0;
}
