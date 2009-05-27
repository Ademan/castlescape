#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <algorithm>
#include <ostream>

#include "math_types.h"

void send_quit(int code);

inline void print_vector(std::ostream & stream, const vec3 & v)
{
    stream <<  "x: " << v[0]
           << " y: " << v[1]
           << " z: " << v[2] << std::endl;
}

#endif /*UTIL_H*/
