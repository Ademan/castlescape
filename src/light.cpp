#include "light.h"

void Light::begin_render()
{
    light.enable(0);
}

void Light::end_render()
{
    light.disable(0);
}

void OrbitingLight::step(const float dtime)
{
    time += dtime;

    light.pos[0] = radius * cos(time);
    light.pos[1] = 0;
    light.pos[2] = radius * sin(time);
}
