#pragma once
#include "enemy.h"
#include "surface.h"

namespace Tmpl8
{
	class WhiteEnemy : public Enemy
	{
	public:
		WhiteEnemy()
		{
			type = WHITE_ENEMY;
		};
		void Update(float* deltaTime, Surface* screen); //Can't be called Update() otherwise we loop into parent Update()
		void Draw(Surface* screen);
	};
}

