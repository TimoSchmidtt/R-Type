#include "precomp.h"
#include "star.h"

namespace Tmpl8
{
	void Star::Update(float* deltaTime, Surface* screen)
	{
		if (x > 0) //If we are on the screen
		{
			x -= speed; //Move down with our speed
		}
		else //Reached bottom of screen
		{
			x = SCRWIDTH; //Move to front

			y = (float)(rand() % SCRHEIGHT); //Random location on the screen
		}
		Draw(screen);
	}

	void Star::Draw(Surface* screen)
	{
		if (bDraw) screen->Plot((int)x, (int)y, 0xffffff);
	}
}