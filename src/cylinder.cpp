#include <GL/gl.h>
#include <cmath>
#include "cylinder.h"

#include "vertex.h"

template <>
struct accessor_t <cylinder_vertex_t>
{
    static float get_x(const cylinder_vertex_t & v) {return v.x;}
    static float get_y(const cylinder_vertex_t & v) {return v.y;}
    static float get_z(const cylinder_vertex_t & v) {return v.z;}

    static float set_x(cylinder_vertex_t & v, const float x) {v.x = x;}
    static float set_y(cylinder_vertex_t & v, const float y) {v.y = y;}
    static float set_z(cylinder_vertex_t & v, const float z) {v.z = z;}

    static float get_nx(const cylinder_vertex_t & v) {return v.nx;}
    static float get_ny(const cylinder_vertex_t & v) {return v.ny;}
    static float get_nz(const cylinder_vertex_t & v) {return v.nz;}

    static void set_nx(cylinder_vertex_t & v, const float nx) {v.nx = nx;}
    static void set_ny(cylinder_vertex_t & v, const float ny) {v.ny = ny;}
    static void set_nz(cylinder_vertex_t & v, const float nz) {v.nz = nz;}
};

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
    *index = 0;
    index++;
    for (unsigned int i = 0; i < subdivisions; i++)
    {
        *index = i + subdivisions;
        index++;
        *index = (i + 1) % subdivisions;
        index++;
    }
    *index = subdivisions;
}

void Cylinder::render()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, sizeof(cylinder_vertex_t), &(vertices[0].x));
    glNormalPointer(GL_FLOAT, sizeof(cylinder_vertex_t), &(vertices[0].nx));

    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    //show_normals(&(vertices[0]), vertices.size());
}
