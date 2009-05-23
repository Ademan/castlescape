#ifndef MOUSE_H
#define MOUSE_H

#include <SDL/SDL.h>
//#include "camera.h"

class Mouse
{
	unsigned int width, height;
	float sensitivity;
	int oldx, oldy;
	int curx, cury;
	int deltax, deltay;

public:
	Mouse(unsigned int _width, unsigned int _height, float _sensitivity): width(_width), height(_height), sensitivity(_sensitivity)  
	{
		SDL_GetMouseState(&curx, &cury);
		oldx = curx;
		oldy = cury;

		deltax = deltay = 0;
	}

	void update()
	{
		SDL_GetMouseState(&curx, &cury);
		deltax = oldx - curx;
		deltay = oldy - cury;
		
		oldx = curx;
		oldy = cury;
		SDL_WarpMouse(width / 2, height / 2);
	}

	void movecamera(Camera cam)
	{
		cam.rotate(deltax * sensitivity, deltay * sensitivity);
	}

	void dragcamera(Camera cam, float relx, float rely)
	{
		cam.rotate(relx, rely);

	}

};

#endif
