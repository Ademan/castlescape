#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "renderable.h"
#include "entity.h"
#include "input_handlers.h"

class Engine
{
    typedef std::vector <IRenderable *> renderable_list;
    typedef renderable_list::iterator   renderable_iter;
    renderable_list renderables;

    typedef std::vector <IRenderState *> render_state_list;
    typedef render_state_list::iterator  render_state_iter;
    render_state_list                    render_states;

    typedef std::vector <Entity *>      entity_list;
    typedef entity_list::iterator       entity_iter;
    entity_list     entities;

    typedef std::vector <IMouseHandler *>   mouse_handler_list;
    typedef mouse_handler_list::iterator    mouse_handler_iter;
    mouse_handler_list      mouse_handlers;

    typedef std::vector <IKeyboardHandler *>    keyboard_handler_list;
    typedef keyboard_handler_list::iterator     keyboard_handler_iter;
    keyboard_handler_list   keyboard_handlers;
public:
    Engine(){}

    void add_mouse_handler(IMouseHandler * handler)
    {mouse_handlers.push_back(handler);}
    void mouse_down(SDL_MouseButtonEvent & event);
    void mouse_up(SDL_MouseButtonEvent & event);
    void mouse_move(SDL_MouseMotionEvent & event);

    void add_keyboard_handler(IKeyboardHandler * handler)
    {keyboard_handlers.push_back(handler);}
    void key_down(SDL_KeyboardEvent & event);
    void key_up(SDL_KeyboardEvent & event);

    void add_renderable(IRenderable * renderable)
    {renderables.push_back(renderable);}
    void render();

    void add_entity(Entity * entity)
    {entities.push_back(entity);}
    void step(const float dtime);

    void add_render_state(IRenderState * render_state)
    {render_states.push_back(render_state);}
    void begin_render();
    void end_render();
};

#endif /*ENGINE_H*/
