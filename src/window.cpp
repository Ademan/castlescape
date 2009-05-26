#include <iostream>
#include <cstdlib>

#include "window.h"

using std::cout;
using std::endl;

Window::Window(unsigned int width, unsigned height,
               const unsigned int bpp = 24, const unsigned int depth = 16)
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
}
