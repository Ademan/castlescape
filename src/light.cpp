#include "light.h"
#include "primitive.h"

int max_lights()
{
    int result = 0;
    glGetIntegerv(GL_MAX_LIGHTS, &result);
    return result;
}

unsigned int next_light()
{
    for (int i = 0; i < max_lights(); i++)
    {
        if (glIsEnabled(gl_index(i)) == GL_FALSE)
            return i;
    }
}

void Light::begin_render()
{
    index = next_light();
    light.enable(index);
}

void Light::end_render()
{
    light.disable(index);
}

void OrbitingLight::step(const float dtime)
{
    time += dtime;

    if (axis == XY)
    {
        light.pos[0] = radius * cos(time);
        light.pos[1] = radius * sin(time);
        light.pos[2] = 0;
    }
    else if (axis == XZ)
    {
        light.pos[0] = radius * cos(time);
        light.pos[1] = 0;
        light.pos[2] = radius * sin(time);
    }
    else if (axis == ZY)
    {
        light.pos[0] = 0;
        light.pos[1] = radius * cos(time);
        light.pos[2] = radius * sin(time);
    }
}

void RenderableOrbitingLight::step(const float dtime)
{
	time += dtime;

    light.pos[0] = radius * cos(time);
    light.pos[1] = radius * sin(time);
    light.pos[2] = 0;
}

void RenderableOrbitingLight::render()
{
	draw_cone(light.pos[0], light.pos[1] + 50, light.pos[2], 10, 10);
	/*glBegin(GL_LINES);
	glVertex3f(light.pos[0], light.pos[1] + 50, light.pos[2]);
	glVertex3f(light.pos[0] + 10, light.pos[1] + 40, light.pos[2]);

	glVertex3f(light.pos[0], light.pos[1] + 50, light.pos[2]);
	glVertex3f(light.pos[0] - 10, light.pos[1] + 40, light.pos[2]);

	glVertex3f(light.pos[0], light.pos[1] + 50, light.pos[2]);
	glVertex3f(light.pos[0], light.pos[1] + 40, light.pos[2] + 10);
	
	glVertex3f(light.pos[0], light.pos[1] + 50, light.pos[2]);
	glVertex3f(light.pos[0], light.pos[1] + 40, light.pos[2] - 10);
	glEnd();*/

}
