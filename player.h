#pragma once
#include "Entity.h"

namespace Tmpl8 {

	class Player : public Entity
	{
	public:
		Player()
		{
			x = 0.0f + SCRWIDTH / 8 - width; //Left of the screen
			y = 0.0f + (SCRHEIGHT / 2) - height; //Middle of screen
			xOffset = 0;
			yOffset = 0;
			width = 64;
			height = 28;
			bActive = true;
			type = PLAYER;
		};
		~Player()
		{
			totalActive--;
		};
		void Draw(Surface* screen);
		void Update(float* deltaTime, Surface* screen);
		
		void HandleCharging();
		void HandlePlayerControls(float* deltaTime);
		void TakeDamage(int amount) { return; }
		void Die();
		void CreateShot(int xType);

		bool drawShotBridge = false;
		int shotBridgeFrame = 7;
		float shotBridgeTimer = 0;
		int speed = 4; //How many pixels the player will move per requested direction
		bool canShoot = true;
		int sprite = 0;
		int chargeFrame = 0;
		float chargeTimer = 0.0f; 
		int chargeBar = 0;
	};
	enum player_states { INTRO = 0, ACTIVE, DEAD, POSTLEVEL };
}