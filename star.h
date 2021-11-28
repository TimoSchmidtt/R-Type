#pragma once
#include "Entity.h"

namespace Tmpl8 {

	class Star : public Entity
	{
	public:
		Star()
		{
			x = (float)(rand() % SCRWIDTH); //Random location
			y = (float)(rand() % SCRHEIGHT); //Random location
			limit = rand() % 1000 + 1000;
			speed = rand() % 7 + 2;
			totalActive++;
			bActive = true;
		};
		~Star() {
			totalActive--;
		};
		void Update(float* deltaTime, Surface* screen);
		void Draw(Surface* screen);
		int speed; //This is the amount of pixels to move per frame.
		int limit;	//How many milliseconds have to pass for us to disappear/rea-ppear
		int timer = 0;	//How long we've waited
	};
}