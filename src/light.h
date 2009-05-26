#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <GL/gl.h>

#include "types.h"

struct light_t
{
    GLuint  index;
    vec3    pos;

};

#endif /*LIGHT_H*/
