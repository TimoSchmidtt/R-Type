#include "precomp.h"
#include "CircleEnemy.h"
namespace Tmpl8
{

	Sprite circleEnemySPR(new Surface("assets/CircleEnemySPR.tga"), 18); //16 + 2 dead
	Sprite mainCircleEnemySPR(new Surface("assets/MainCircleEnemySPR.tga"), 18); //16 + 2 dead
	
	void CircleEnemy::DetermineAngle() //Changes frame to match the angle
	{
		//NOT FINISHED
		float degree = atan2(velocity[1] - 0, velocity[0] - 0) * 180 / 3.14f;
		frame = (int)(round(degree / 22.5f) + 4);
		if (frame < 0) frame += 16;
		frame %= 16;
	}

	
	void CircleEnemy::Update(float* deltaTime, Surface* screen)
	{
		//Rotate
		if (head)
		{
			//if die rest die
		}
		else
		{
			//if die, die
		}
		Draw(screen);
	}

	void CircleEnemy::Draw(Surface* screen)
	{
		if (head)
		{
			mainCircleEnemySPR.SetFrame(frame);
			mainCircleEnemySPR.Draw(screen, (int)x, (int)y);
		}
		else
		{
			circleEnemySPR.SetFrame(frame);
			circleEnemySPR.Draw(screen, (int)x, (int)y);
		}
	}
}
