#include "engine.h"
#include <algorithm>

using std::for_each;

void Engine::render()
{
    for (renderable_iter i = renderables.begin();
         i != renderables.end(); i++)
    {
        (*i)->render();
    }
}

void Engine::step(const float dtime)
{
    for (entity_iter i = entities.begin();
         i != entities.end(); i++)
    {
        (*i)->step(dtime);
    }
}


