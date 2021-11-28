#include "precomp.h"
#include "shot.h"
#include "game.h" //Used for the enum
#include "player.h" //Tilemap collision
#include "Camera.h"
#include "2DCollision.h"
#include "UpgradeFriend.h"

namespace Tmpl8
{	
	int Shot::playerShots = 0;
	extern Entity* allEntities[300];
	extern int level1Map[20][300];

	float gravity = .1f;

	void Shot::Die()
	{
		totalActive--;
		bActive = false;
	}

	void Shot::HitDetection() //Detects Entity-Entity detection.
	{
		int n = allEntities[0]->totalActive;
		for (int i = 0; (i < sizeof(allEntities) / sizeof(Entity*)) && (i < n + i); i++)
		{

			if (!allEntities[i]) continue; //Skip nullptrs
			if (allEntities[i]->bUnhittable) continue; //Can't hit what you can't hit

			if (allEntities[i]->bActive)
			{
				if (!((allEntities[i]->type >= SHOT1) && (allEntities[i] > 0)))
				{
					if (!friendly) //If we should be finding the player
					{
						if (allEntities[i]->type == PLAYER || allEntities[i]->type == UPGRADE_FRIEND)
							if (Collision2D::AABBOverlap((Entity*)this, allEntities[i]))
							{
								allEntities[i]->TakeDamage(damage);
								if (!piercing)
									Die();
								break;
							}
					}
					else if(friendly) //If we should be finding enemies
					{
						if (allEntities[i]->type != PLAYER && allEntities[i]->type != UPGRADE_FRIEND)
							if (Collision2D::AABBOverlap((Entity*)this, allEntities[i]))
							{
								allEntities[i]->TakeDamage(damage);
								if (!piercing)
									Die();
								break;
							}
					}
				}
			}
		}
	}

	void Shot::Update(float* deltaTime, Surface* screen)
	{
		Entity* player = GetEntityFromType(PLAYER);
		if (Collision2D::didEntityHitTile(this))
		{
			if(!(type >= RED_UPGRADE_SHOT))
				Die();
		}

		HitDetection();

		if (bActive)
		{
			switch (type)
			{
			case MISSLESHOT:
			{
				velocity[1] += gravity; // gravity = .1f;
				//Projectile motion
				break;
			}
			case RED_UPGRADE_BRIDGE:
			{
				//stick to player
				if (frame < 7)
				{
					velocity[0] = player->velocity[0];
					velocity[1] = player->velocity[1];
				}
				else 
				{
					velocity[1] = player->velocity[1];
					velocity[0] = player->velocity[0] + 4.9f;
				}
				break;
			}
			case RED_UPGRADE_BRIDGE_BRIDGE:
			{
				velocity[1] = 0.0f;
				velocity[0] = 5.8f;
			}
			default:
			{
				break;
			}
			}
			x += velocity[0];
			y += velocity[1];

			frameTimer += *deltaTime;
		}
		if (x > SCRWIDTH ||
			y > SCRHEIGHT ||
			x + width  < 0 ||
			y + height < 0)
		{
			Die();
		}
		Draw(screen);
	}

	void Shot::Draw(Surface* screen)
	{
		if(type > SHOT1 && type <= CHARGE5) //Missleshot is based off of velocity, not this.
			if (frameTimer >= 50)
				{
					frame++;
					frameTimer = 0;
				}

		switch (type)
		{
			case SHOT1:
			{
					if (frame > 2) //This one "grows" to it's final form
					{
						frame = 2;
					}
					break;
				}
			case MISSLESHOT:
			{
					float degree = atan2(velocity[1], velocity[0]) * 180 / 3.14f;
					frame = (int)((degree / 20)) + 4;
					if (frame < 0) frame += 18;
					frame %= 18;
					
					break;
				}
			case RED_UPGRADE_BRIDGE:
			{
				if (frameTimer >= 30)
				{
					frame++;
					frameTimer = 0;
				}
				if (frame >= 14)
				{
					width = 127;
					height = 88;
					y += 12;
					frame = 0;
					type = RED_UPGRADE_BRIDGE_BRIDGE;
					sprite = &UpgradeFriend::upgradeShotRedBridgeBridgeSPR;
				}
				break;
			}
			case RED_UPGRADE_BRIDGE_BRIDGE:
			{
				if (frameTimer >= 30)
				{
					frame++;
					frameTimer = 0;
				}
				if (frame >= 10)
				{
					x -= 3;
					y += 14;
					width = 127;
					height = 63;
					frame = 0;
					type = RED_UPGRADE_SHOT;
					sprite = &UpgradeFriend::upgradeShotRedSPR;
				}
				break;
			}
			case RED_UPGRADE_SHOT:
			{
				if (frameTimer >= 30)
				{
					frame++;
					frameTimer = 0;
				}
				if (frame >= 8)
				{
					frame = 0;
				}
				break;
			}
			default:
			{
					if (frame > 1) //causes flicker for the chargeshots
					{
						frame = 0;
					}
					break;
				}
		}
		
		if (sprite)
		{
			sprite->SetFrame(frame);
			sprite->Draw(screen, (int)x, (int)y);
		}
		else
		{
			for (int i = 0; i < 99; i++)
				printf("SHOT->SPRITE NOT SET!");
		}
	}
}