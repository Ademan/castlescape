#include "engine.h"
#include <algorithm>

void Engine::render()
{
    for (renderable_iter i = renderables.begin(); i != renderables.end(); i++)
    {
        (*i)->render();
    }
}

//FIXME: for_each somehow!
void Engine::step(const float dtime)
{
    for (entity_iter i = entities.begin();
         i != entities.end(); i++)
    {
        (*i)->step(dtime);
    }
}

void Engine::mouse_down(SDL_MouseButtonEvent & event)
{
    for (mouse_handler_iter i = mouse_handlers.begin();
         i != mouse_handlers.end(); i++)
    {
        (*i)->mouse_down(event);
    }
}

void Engine::mouse_up(SDL_MouseButtonEvent & event)
{
    for (mouse_handler_iter i = mouse_handlers.begin();
         i != mouse_handlers.end(); i++)
    {
        (*i)->mouse_up(event);
    }
}

void Engine::mouse_move(SDL_MouseMotionEvent & event)
{
    for (mouse_handler_iter i = mouse_handlers.begin();
         i != mouse_handlers.end(); i++)
    {
        (*i)->mouse_move(event);
    }
}

void Engine::key_down(SDL_KeyboardEvent & event)
{
    for (keyboard_handler_iter i = keyboard_handlers.begin();
         i != keyboard_handlers.end(); i++)
    {
        (*i)->key_down(event);
    }
}

void Engine::key_up(SDL_KeyboardEvent & event)
{
    for (keyboard_handler_iter i = keyboard_handlers.begin();
         i != keyboard_handlers.end(); i++)
    {
        (*i)->key_up(event);
    }
}

void Engine::begin_render()
{
    for (render_state_iter i = render_states.begin();
            i != render_states.end(); i++)
        (*i)->begin_render();
}

void Engine::end_render()
{
    for (render_state_iter i = render_states.begin();
            i != render_states.end(); i++)
        (*i)->end_render();
}
