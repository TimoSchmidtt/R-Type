#pragma once
#include "Entity.h"

namespace Tmpl8 {

	class Shot : public Entity
	{
	private:
		void Shot::HitDetection();
		void Shot::DidWeHitTileMap();
	public:
		Shot()
		{
		};
		~Shot()
		{
		};
		
		void Update(float* deltaTime, Surface* screen);
		void Draw(Surface* screen);
		int speed = 3; //Speed to move upward
		void Die();
		Sprite* sprite;

		static int playerShots;
		bool piercing = false;
		int damage = 0;
		int frame = 0;
		bool friendly = true;
		float frameTimer = 0;
	};
}

