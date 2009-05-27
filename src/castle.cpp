#include <ctime>
#include <cstdlib>

#include <GL/gl.h>

#include "castle.h"
#include "primitive.h"
#include "transform.h"

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
    return (low - high) * random(0, 1024) / 1024.0f + low;
}

Castle::Castle()
{
    body.body.position.position[0] = random(-32.0f, 32.0f);
    body.body.position.position[2] = random(-32.0f, 32.0f);

    body.body.scaling.scaling[1] = random(16, 32);
    body.body.scaling.scaling[0] = body.body.scaling.scaling[2] = random(16, 64);
    body.body.position.position[1] = 0.33 * body.body.scaling.scaling[1];
}

void Castle::render()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadIdentity();
    body.body.apply();
    draw_cube();
    glPopMatrix();
}
