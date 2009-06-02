#include <cmath>
#include "cylinder.h"

const size_t Cylinder::vertex_count(const unsigned int subdivisions)
{return subdivisions * 2;}

const size_t Cylinder::index_count(const unsigned int subdivisions)
{return subdivisions * 2 + 2;}

Cylinder::Cylinder(const unsigned int subdivisions)
{
    vertices.resize(Cylinder::vertex_count(subdivisions));
    indices.resize(Cylinder::index_count(subdivisions));

    float step = 2.0 * M_PI / subdivisions;

    vertex_iter top = vertices.begin();
    vertex_iter bottom = vertices.begin() + subdivisions;

    for (unsigned int i = 0; i < subdivisions; i++)
    {
        top->x = bottom->x = cos(step * i);
        top->nx = bottom->nx = cos(step * i);

        top->z = bottom->z = sin(step * i);
        top->nz = bottom->nz = sin(step * i);

        top->ny = bottom->ny = 0;
        top->y = 1.0;
        bottom->y = -1.0;

        top++;
        bottom++;
    }

    index_iter index = indices.begin();

    //FIXME: haven't given index generation much thought at all!
    *index++ = 0;
    for (unsigned int i = 0; i < subdivisions; i++)
    {
        *index++ = i + subdivisions;
        *index++ = i + 1;
    }
    *index = subdivisions;
}

void Cylinder::render()
{

}
