#include <cmath>
#include <GL/gl.h>

#include "cone.h"

const size_t    Cone::vertex_count(const unsigned int subdivisions)
{return 1 + subdivisions;}

const size_t    Cone::index_count(const unsigned int subdivisions)
{return 2 + subdivisions;}

Cone::Cone(const int subdivisions)
{
    vertices.resize(Cone::vertex_count(subdivisions));
    indices.resize(Cone::index_count(subdivisions));

    float step = 2 * M_PI / subdivisions;

    vertex_iter v = vertices.begin();
    for (unsigned int i = 0; i < subdivisions; i++)
    {
        v->x = cos(step * i);
        v->y = 0;
        v->z = sin(step * i);
        v++;
    }
    v->x = v->z = 0;
    v->y = 1.0;

    index_iter index = indices.begin();

    *index++ = subdivisions;
    for (unsigned int i = 0; i < subdivisions; i++)
    {
        *index++ = i;
    }
    *index = 0;

}

void Cone::render()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(cone_vertex_t),
                    &(vertices[0].x));

    glDrawElements(GL_TRIANGLE_FAN, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));

    glDisableClientState(GL_VERTEX_ARRAY);
}
