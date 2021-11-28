#include "precomp.h"
#include "YellowEnemy.h"

namespace Tmpl8
{
	Sprite yellowEnemySPR(new Surface("assets/YellowEnemySPR.tga"), 16); //16 degree

	/*
	* x: 22.5 degree
	*/

	/*
		First 5 Yellow:

		Move up + left until world coordinate
		Velocity down from world coordinate ()
		After world coordinate, speed up

	*/

	void YellowEnemy::DetermineAngle() //Changes frame to match the angle
	{
		float degree = atan2(velocity[1], velocity[0]) * 180 / 3.14f;
		frame = int(round(degree / 22.5f)) + 4; //22.5f = 360/16
		if (frame < 0) frame += 16;
		frame %= 16;
	}

	void YellowEnemy::Update(float* deltaTime, Surface* screen)
	{
		x += velocity[0];
		y += velocity[1];

		switch (state)
		{
		case FIRST_ENCOUNTER:
		{
			break;
		}
		case ZIG_ZAG:
		{
			velocity[0] = (float)-speed;
			velocity[1] = (sin((steps * (counter)) * 3.141f / degrees) * radius) * 0.075f; //This WORKS. DO NOT TOUCH IT.
			counter++;
			break;
		}
		case SPIN:
		{
			steps = 3;
			degrees = 360.0f;
			radius = 5;
			velocity[0] = (cos((steps * (counter)) * 3.141f / degrees) * radius);
			velocity[1] = (sin((steps * (counter)) * 3.141f / degrees) * radius); //This WORKS. DO NOT TOUCH IT.
			counter++;
			break;
		}
		case CORNER_FROM_TOP:
		{

			break;
		}
		default:
		{
			for (int i = 0; i < 99; i++)printf("UNKNOWN YELLOWENEMY::UPDATE() STATE");
			break;
		}
		}



		DetermineAngle();
		if (bShoot)
		{
			NormalShootAtPlayer();
		}

		Draw(screen);
	}

	void YellowEnemy::Draw(Surface* screen)
	{
		yellowEnemySPR.SetFrame(frame);
		yellowEnemySPR.Draw(screen, (int)x, (int)y);
	}
}

