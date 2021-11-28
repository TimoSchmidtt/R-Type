#pragma once
#include "Entity.h"

namespace Tmpl8 {

	class Camera : public Entity
	{
	public:
		Camera()
		{
			type = CAMERA;
			x = 0.0f;
			y = 0.0f; //Lower eight of the screen
		};
		void Update(float* deltaTime, Surface* screen);
		bool move = false;
		float speed = 1.0f;
		float end = 8000;
	};
}