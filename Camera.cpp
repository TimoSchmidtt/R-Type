#include "precomp.h"
#include "Camera.h"

namespace Tmpl8
{
	void Camera::Update(float* deltaTime, Surface* screen)
	{
		//Camera Movement
		if (x >= end)
			move = false;

		if (move)
		{
			x += speed;
			y;
		}	
	}
}