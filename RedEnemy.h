#pragma once
#include "enemy.h"

namespace Tmpl8
{
	class RedEnemy : public Enemy
	{
	public:
		RedEnemy()
		{
			totalActive++;
			type = RED_ENEMY;
			xOffset = 7;
			yOffset = 11;
			speed = 4;
			width = 44;
			height = 46;
		};

		// cos / sin variables
		int pivotPoint[2] = { 0, 0 };
		int counter = 0;
		int steps = 4;
		float degrees = 180.0f;
		int radius = 60;

		void Update(float* deltaTime, Surface* screen);
		void Draw(Surface* screen);
	};
}