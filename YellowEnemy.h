#pragma once
#include "enemy.h"

namespace Tmpl8
{
	class YellowEnemy : public Enemy
	{
	public:
		YellowEnemy()
		{
			type = YELLOW_ENEMY;
			frame = 0;
			width = 53;
			height = 45;
			health = 1;
		};
		void Update(float* deltaTime, Surface* screen); //Can't be called Update() otherwise we loop into parent Update()
		void Draw(Surface* screen);
		void DetermineAngle();

		enum {FIRST_ENCOUNTER = 0, ZIG_ZAG, CORNER_FROM_TOP, SPIN};
		int frame = 0; //Frame is also the direction. (degree/22.5) - 1 = frame
		int pivotPoint[2] = { 0, 0 };
		int counter = 0;
		int steps = 3;
		float degrees = 180.0f;
		int radius = 30;
	};
}

