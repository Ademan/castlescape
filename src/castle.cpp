#include <ctime>
#include <cstdlib>

#include <iostream>

#include <GL/gl.h>

#include "castle.h"
#include "primitive.h"
#include "transform.h"
#include "util.h"

using std::cout;
using std::rand; using std::srand;
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
    //FIXME: should be some sort of parameter
    float h = 0.5; //height ratio
    float hwidth = bwidth / 2.0;
    //float hbase = body.scaling.scaling[0] / 2.0;
    float hbase = 0.5;

    castle_transform battlement;

    battlement.scaling.scaling[0] = bwidth;
    battlement.scaling.scaling[1] = bwidth * h;
    battlement.scaling.scaling[2] = bwidth;

    battlement.position.position[1] = bwidth * h / 2.0;


    //southwest
    battlement.position.position[0] = -hbase + hwidth;
    battlement.position.position[2] = -hbase + hwidth;
    battlements.push_back(battlement);

    //northwest
    battlement.position.position[0] = -hbase + hwidth;
    battlement.position.position[2] = hbase - hwidth;
    battlements.push_back(battlement);

    //northeast
    battlement.position.position[0] = hbase - hwidth;
    battlement.position.position[2] = hbase - hwidth;
    battlements.push_back(battlement);

    //southeast
    battlement.position.position[0] = hbase - hwidth;
    battlement.position.position[2] = -hbase + hwidth;
    battlements.push_back(battlement);
}

void cube_with_battlements::generate_battlements()
{
    int n = random(0, 8);
    float r = 0.5; //gap ratio
    float t = 0.4; //thickness ratio
    //FIXME: bad math!
    //float b = body.scaling.scaling[0] / (n + r*n - r);
    float b = 0.125;
    float g = r * b;

    castle_transform battlement;

    generate_corners(b);
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

    body.generate_battlements();

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
            glTranslatef(0, 0.5, 0);
            for (int i = 0; i < battlements.size(); i++)
            {
                glPushMatrix();
                battlements[i].apply();
                draw_cube();
                glPopMatrix();
            }
        glPopMatrix();
    glPopMatrix();
}

void Castle::render()
{
    glColor3f(0.7, 0.7, 0.7);
    body.draw();
}
