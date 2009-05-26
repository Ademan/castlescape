#include "light.h"
#include "primitive.h"

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

void RenderableOrbitingLight::step(const float dtime)
{
	time += dtime;

    light.pos[0] = radius * cos(time);
    light.pos[1] = 0;
    light.pos[2] = radius * sin(time);
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
