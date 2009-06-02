#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>

class Timer
{
    unsigned int    last;
public:
    Timer() {last = SDL_GetTicks();}
    const float elapsed()
    {
        unsigned int    now = SDL_GetTicks();
        float           result = (now - last) / 1000.0f;
        last = now;
        return result;
    }
	const float peek()
	{
		return (SDL_GetTicks() - last) / 1000.0f;
	}
};

#endif /*TIMER_H*/
