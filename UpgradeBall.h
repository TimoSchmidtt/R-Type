#pragma once
#include "Entity.h"

namespace Tmpl8 {

	class UpgradeBall : public Entity
	{
		void Update(float* deltaTime, Surface* screen);
		void Draw(Surface* screen);
	};
}
