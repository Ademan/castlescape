#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

class IRenderable
{
public:
    virtual void render() = 0;
};

class IRenderState
{
public:
    virtual void begin_render() = 0;
    virtual void end_render() = 0;
};

#endif /*RENDERABLE_H*/
