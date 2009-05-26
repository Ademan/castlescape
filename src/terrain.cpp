#include "terrain.h"
#include "types.h"

using cml::matrix_scale;
using cml::matrix_translation;

void Terrain::render()
{
    mat4    translation;
    mat4    scale;

    matrix_scale(scale, scaling);
    matrix_translation(translation, position);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf((translation * scale).data());

    terrain.render();

    glPopMatrix();
}
