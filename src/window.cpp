#include <iostream>
#include <cstdlib>

#include <GL/gl.h>
#include "window.h"

using std::cout;
using std::endl;

Window::Window(unsigned int width, unsigned height,
               const unsigned int bpp, const unsigned int depth,
               const float clear_color[4], const float clear_depth)
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, depth );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    window = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL);

    if (!window)
    {
        cout << "Failed to create window!!" << endl;
    }

    glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
    glClearDepth(clear_depth);
}
