#include "precomp.h"
#include "TurretEnemy.h"
namespace Tmpl8
{
	Sprite turretSPR(new Surface("assets/TurretSPR.tga"), 12); //6 floor left -> right, 6 ceiling left -> right

	void TurretEnemy::DetermineSpriteFrame(Entity* player)
	{
		if (!player) return; //If the player is a nullptr
		if (state == FLOOR)
		{

			float divider = 50.0f;
			if (frame > 2) divider = 30.0f;
			float degree = atan2(player->x - x, -(player->y - y)) * 180 / 3.14f;
			frame = int(round(degree / divider)) + 2;
			if (frame < 0) frame += 6;
			if (frame > 5) frame = 5;
		}
		else
		{
			float divider = 50.0f;
			if (frame > 8) divider = 30.0f;

			float degree = atan2(player->x - x, player->y - y) * 180 / 3.14f;
			frame = int(round(degree / divider)) + 8;
			if (frame < 6) frame = 6;
			if (frame > 11) frame = 11;
		}
	}
	
	void TurretEnemy::Update(float* deltaTime, Surface* screen)
	{
		DetermineSpriteFrame(Entity::GetEntityFromType(PLAYER));
		
		
		if (bShoot)
			NormalShootAtPlayer();

		Draw(screen);
	}

	void TurretEnemy::Draw(Surface* screen)
	{
		turretSPR.SetFrame(frame);
		turretSPR.Draw(screen, (int)x, (int)y);
	}
}