#include <ctime>
#include <cstdlib>

#include <iostream>

#include <GL/gl.h>

#include "castle.h"
#include "primitive.h"
#include "transform.h"
#include "util.h"

using std::cout;
using std::endl;
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

void cube_with_battlements::generate_battlement(castle_transform & battlement, float x, float y)
{
    battlement.position.position[0] = x;
    battlement.position.position[2] = y;
}

void cube_with_battlements::generate_corners(castle_transform & battlement,
                                             float hwidth)
{
    const float hbase = 0.5;
    //southwest
    generate_battlement(battlement, -hbase + hwidth, -hbase + hwidth);
    battlements.push_back(battlement);

    //northwest
    generate_battlement(battlement, -hbase + hwidth, hbase - hwidth);
    battlements.push_back(battlement);

    //northeast
    generate_battlement(battlement, hbase - hwidth, hbase - hwidth);
    battlements.push_back(battlement);

    //southeast
    generate_battlement(battlement, hbase - hwidth, -hbase + hwidth);
    battlements.push_back(battlement);
}

void cube_with_battlements::generate_battlements()
{
    int n = random(4, 8);
    float r = 0.5; //gap ratio
    float t = 0.4; //thickness ratio
    //FIXME: bad math?
    float b = 1 / (n + r*n - r);

    float g = r * b;
    float h = 0.5; //height ratio
    float hwidth = b / 2.0;
    float hbase = 0.5; //half base size

    castle_transform battlement;

    battlement.scaling.scaling[0] = b;
    battlement.scaling.scaling[1] = b * h; //height ratio times battlement width
    battlement.scaling.scaling[2] = b;

    //set battlement base
    battlement.position.position[1] = b * h / 2.0;

    generate_corners(battlement, b / 2.0);

    //south battlement array
    for (int i = 0; i < (n - 2); i++)
    {
        generate_battlement(battlement, hwidth - hbase + (g + b) * (i + 1), hwidth - hbase);
        battlements.push_back(battlement);
    }

    //north battlement array
    for (int i = 0; i < (n - 2); i++)
    {
        generate_battlement(battlement, hwidth - hbase + (g + b) * (i + 1), -hwidth + hbase);
        battlements.push_back(battlement);
    }
    
    //west battlement array
    for (int i = 0; i < (n - 2); i++)
    {
        generate_battlement(battlement, hwidth - hbase, hwidth - hbase + (g + b) * (i + 1));
        battlements.push_back(battlement);
    }
    
    //east battlement array
    for (int i = 0; i < (n - 2); i++)
    {
        generate_battlement(battlement, -hwidth + hbase, hwidth - hbase + (g + b) * (i + 1));
        battlements.push_back(battlement);
    }
}

Castle::Castle()
{
    body.body.position.position[0] = random(-64.0f, 64.0f);
    body.body.position.position[2] = random(-64.0f, 64.0f);

    body.body.scaling.scaling[1] = random(8, 16);
    body.body.scaling.scaling[0] = body.body.scaling.scaling[2] = random(4, 24);
    body.body.position.position[1] = 0.33 * body.body.scaling.scaling[1];

    body.generate_battlements();

    keep.body.scaling.scaling[1] = random(0.25f, 0.75f);
    keep.body.scaling.scaling[0] = keep.body.scaling.scaling[2] = 1 / random(4.0f, 2.0f);

    //keep.body.position.position[0] = random(-0.5f, 0.5f);
    //keep.body.position.position[2] = random(-0.5f, 0.5f);
    keep.body.position.position[0] = keep.body.position.position[2] = 0;

    keep.body.position.position[1] = keep.body.scaling.scaling[1] / 2.0;
    keep.generate_battlements();
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

//FIXME: remove redundant push/pops and transformations
void Castle::render()
{
    glColor3f(0.7, 0.7, 0.7);
    body.draw();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        body.body.apply();
        glTranslatef(0, 0.5, 0);
        keep.draw();
    glPopMatrix();
}
