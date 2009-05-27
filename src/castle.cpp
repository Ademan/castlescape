#include <ctime>
#include <cstdlib>

#include <iostream>

#include <GL/gl.h>

#include "castle.h"
#include "primitive.h"
#include "transform.h"
#include "util.h"

using std::cout;
using std::rand;
using std::srand;
using std::time;

const int random(const int low, const int high)
{
    int range = (high - low);
    return (rand() % range) + low;
}

const float random(const float low, const float high)
{
    return (high - low) * random(0, 1024) / 1024.0f + low;
}

void cube_with_battlements::generate_corners(float bwidth)
{
    castle_transform battlement;
}

void cube_with_battlements::generate_battlements()
{
    int n = random(0, 8);
    float r = 0.5;
    //FIXME: bad math!
    float b = body.scaling.scaling[0] / (n + r*n - r);
    float g = r * b;

    castle_transform battlement;
    //battlement.b

    //southwest battlement
}

Castle::Castle()
{
    body.body.position.position[0] = random(-64.0f, 64.0f);
    body.body.position.position[2] = random(-64.0f, 64.0f);

    body.body.scaling.scaling[1] = random(8, 16);
    body.body.scaling.scaling[0] = body.body.scaling.scaling[2] = random(4, 24);
    body.body.position.position[1] = 0.33 * body.body.scaling.scaling[1];

    /*cout << "position: ";
    print_vector(cout, body.body.position.position);

    cout << "scaling: ";
    print_vector(cout, body.body.scaling.scaling);*/
}

void cube_with_battlements::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        body.apply();
        draw_cube();
        glPushMatrix();
            glTranslatef(0, body.scaling.scaling[1], 0);
            /*for (int i = 0; i < body.battlements.length(); i++)
            {
                glPushMatrix();
                body.battlements[i].apply();
                draw_cube();
                glPopMatrix();
            }*/
        glPopMatrix();
    glPopMatrix();
}

void Castle::render()
{
    glColor3f(0.7, 0.7, 0.7);
    body.draw();
}
