#include "precomp.h" // include this first in every .cpp file
#include "RedEnemy.h"

namespace Tmpl8
{
	Sprite redEnemy(new Surface("assets/RedEnemy.tga"), 16); //8 roll facing left, 8 roll facing right
	

	void RedEnemy::Update(float* deltaTime, Surface* screen)
	{

		frameTimer += *deltaTime;
		if (frameTimer > 33)
		{
			frameTimer = 0;
			if (frame < 7)
			{
				frame++;
			}
			else
			{
				frame = 0;
			}
		}


		switch (state)
		{
		case 0:
		{
			pivotPoint[1] = (int)y;
			state++;
			break;
		}
		case 1:
		{
			counter++;
			x -= speed;
			y = pivotPoint[1] - (sin((steps * (counter)) * 3.141f / degrees) * radius);

			if (bShoot)
			{
				NormalShootAtPlayer();
				//shoot = false;
			}

			if (x + width < 0) //If we're off the screen
			{
				totalActive--;
				bActive = false;
			}

			break;
		}
		default:
		{
			break;
		}
		}
		Draw(screen);
	}

	void RedEnemy::Draw(Surface* screen)
	{
		redEnemy.SetFrame(frame);
		redEnemy.Draw(screen, (int)x, (int)y);
	}
}