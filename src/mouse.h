#ifndef MOUSE_H
#define MOUSE_H

#include <SDL/SDL.h>
#include "camera.h"

class Mouse
{
	unsigned int width, height;
	float sensitivity;
	int midx, midy;
	int curx, cury;
	int deltax, deltay;
    Camera * camera;

public:
	Mouse(Camera * _camera, unsigned int _width, unsigned int _height, float _sensitivity): camera(_camera), width(_width), height(_height), sensitivity(_sensitivity)  
	{
		SDL_GetMouseState(&curx, &cury);

		midx = width / 2;
		midy = height / 2;
		
		SDL_WarpMouse(midx, midy);

		deltax = deltay = 0;
	}

	void update()
	{
		SDL_GetMouseState(&curx, &cury);
		SDL_WarpMouse(width / 2, height / 2);
		deltax = (midx - curx) * -1;
		deltay = midy - cury;
		
		if (deltax || deltay) 
			camera->rotate(deltax * sensitivity, deltay * sensitivity);
	}

	void dragcamera(float relx, float rely)
	{
		camera->rotate(relx, rely);
	}

};

#endif
