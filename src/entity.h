#pragma once

#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    virtual void step(const float dtime) = 0;
};

#endif /*ENTITY_H*/
