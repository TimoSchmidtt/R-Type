#pragma once
#include "Entity.h"
#include "game.h"
namespace Tmpl8 {

	class Enemy : public Entity
	{
	public:
		Enemy()
		{};
		virtual void Update(float* deltaTime, Surface* screen) = 0;
		virtual void Draw(Surface* screen) = 0;
		virtual void Die(); //Can't be a pure virtual yet
		virtual void TakeDamage(int amount); //Can't be a pure virtual yet
		void NormalShootAtPlayer();
		
		int health = 0; //How much health we got
		bool bShoot = false; //Should we shoot
		float frameTimer = 0; //Timer used to change frames
		float shootTimer = 0; //Timer used to determine when to shoot

		int speed = 4; //Speed to move
		int frame = 0; //Current frame
	};
	
}