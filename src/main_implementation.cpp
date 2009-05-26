#include <cstdlib>

#include <iostream>
#include <GL/glu.h>

#include "main.h"
#include "util.h"

using std::cout;
using std::cerr;
using std::endl;

Main::Main(unsigned int width, unsigned int height,
           int argc, char ** argv)
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

    if (argc != 2)
    {
        cout << "Need an image file!" << endl;
        exit(1);
    }
    else
        terrain = new Terrain <terrain_vertex_t>(argv[1]);
		cout << "Vertices: " << terrain->get_vertex_count() << endl;
		cout << "Indices: " << terrain->get_index_count() << endl;

}

Terrain<terrain_vertex_t> * terrain;
