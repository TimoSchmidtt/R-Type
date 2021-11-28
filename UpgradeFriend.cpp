#include "precomp.h"
#include "UpgradeFriend.h"
#include "2DCollision.h"
#include "shot.h"

namespace Tmpl8
{
	Sprite upgradeFriend1SPR(new Surface("assets/UpgradeFriend1SPR.tga"), 12); //6 left, 6 right
	Sprite upgradeFriend2SPR(new Surface("assets/UpgradeFriend2SPR.tga"), 12); //6 left, 6 right

	
	Sprite upgradeShotRedBridgeSPR(new Surface("assets/UpgradeShotRedBridgeSPR.tga"), 28);
	Sprite UpgradeFriend::upgradeShotRedSPR(new Surface("assets/UpgradeShotRedSPR.tga"), 16);
	Sprite UpgradeFriend::upgradeShotRedBridgeBridgeSPR(new Surface("assets/UpgradeShotRedBridgeBridgeSPR.tga"), 20);

	Sprite upgradeFriend1AloneShotSPR(new Surface("assets/UpgradeFriend1AloneShotSPR.tga"), 2); //Front and back

	void UpgradeFriend::DetectStickToPlayer(Entity* player)
	{
		if (!Collision2D::AABBOverlap(this, player)) return; //If we aren't overlapping, we shouldn't do anything.

		y = player->y + player->height - height + 10; //+10 so we stick to the nose of the ship
		linked = true;
		if (x > player->x + player->width/2 - 5) //-5 so we are a bit more centered.
		{
			front = true;
			x = player->x + player->width;
		}
		else
		{
			front = false;
			x = player->x - width;
		}

		state = STAY_PLAYER;
	}

	void UpgradeFriend::Update(float* deltaTime, Surface* screen)
	{
		frameTimer += *deltaTime;
		Entity* player = Entity::GetEntityFromType(PLAYER);
		x += velocity[0];
		y += velocity[1];
		
		if (bShoot)
			Shoot();

		switch (state)
		{
			case DEFAULT:
			{
				if (x <= SCRWIDTH - SCRWIDTH / 3)
				{
					velocity[0] = (float)speed;
				}
				else if (x > SCRWIDTH - SCRWIDTH / 3 + 5)
				{
					velocity[0] = (float)-speed;
				}
				else
				{
					velocity[0] = 0;
				}

				velocity[1] = ((float)-speed * (x - player->x > 0.0f)) + ((float)speed * (x - player->x < 0.0f));

				DetectStickToPlayer(player);			
				break;
			}
			case GOTO_PLAYER:
			{
				int dX = (int)(x - player->x + player->width/2);
				int dY = (int)(y - player->y + player->height/2);
				if (dX < 0)
				{
					velocity[0] = (float)speed;
				}
				else if (dX != 0)
				{
					velocity[0] = (float)-speed;
				}
				if (dY < 0)
				{
					velocity[1] = (float)speed;
				}
				else if (dY != 0)
				{
					velocity[1] = (float)-speed;
				}
				DetectStickToPlayer(player);

				break;
			}
			case STAY_PLAYER:
			{
				velocity[0] = player->velocity[0];
				velocity[1] = player->velocity[1];
			
				break;
			}
			case BOOST:
			{
				linked = false;
				hurt = true;
				velocity[0] = -8.0f + 16.0f * (float)front; //Front is true == 1; Front is false == 0: front = 8, not front = -8.
				if ((x <= width + 10.0f) || (x >= SCRWIDTH - width - 30.0f))
				{
					hurt = false;
					state = DEFAULT;
				}
				break;
			}
			default:
			{
				printf("UNINITIALIZED UpgradeFriend::Update() state.");
				break;
			}
		}
		DetermineFrame();
		Draw(screen);
	}
	
	void UpgradeFriend::Shoot()
	{
		bShoot = false;

		if (linked)
		{
			ShootUpgrade();
		}
		else
		{
			ShootAlone();
		}
		
	}

	void UpgradeFriend::ShootUpgrade()
	{
		//if(level == 3)
		switch (currentUpgrade)
		{
			case BLUE_UPGRADE:
			{

				break;
			}
			case RED_UPGRADE: 
			{
				Entity* shot = new Shot();
				shot->x = x + width / 2 - 15;
				shot->y = y + height / 2 - 60;
				shot->type = RED_UPGRADE_BRIDGE;
				shot->velocity[0] = 4;
				shot->width = 127;
				shot->height = 111;
				((Shot*)shot)->friendly = true;
				((Shot*)shot)->sprite = &upgradeShotRedBridgeSPR;
				((Shot*)shot)->piercing = true;

				Entity::CreateEntity(shot);
				break;
			}
			case YELLOW_UPGRADE:
			{

				break;
			}
			default:
			{
				break;
			}
		}
	}

	void UpgradeFriend::ShootAlone()
	{

		switch (level)
		{
		case 1:
		{
			Entity* shot = new Shot();
			shot->x = x + width / 2;
			shot->y = y + height / 2;
			shot->type = UPGRADEFRIENDSHOT;
			shot->velocity[0] = 4;
			shot->width = 32;
			shot->height = 8;
			((Shot*)shot)->damage = 1;
			((Shot*)shot)->friendly = true;
			((Shot*)shot)->sprite = &upgradeFriend1AloneShotSPR;
			Entity::CreateEntity(shot);

			break;
		}
		case 2:
		{
			//Shoot up, down
			break;
		}
		case 3:
		{
			//Shoot all 3 directions (i think)

			break;
		}
		default:
		{
			printf("ERR: Unexpected 'level' in UpgradeFriend::Shoot();");
			break;
		}

		}
	}

	void UpgradeFriend::DetermineFrame()
	{
		//We don't have things for zero velocity so the UpgradeFriend keeps spinning

		if (velocity[0] < 0.0f || velocity[1] > 0.0f) //If moving down or left
		{
			rotateUp = false;
		}
		if (velocity[0] > 0.0f || velocity[1] < 0.0f) //If moving right or up
		{
			rotateUp = true;
		}

		if (int(frameTimer) > 50)
		{
			frameTimer = 0;
			if(rotateUp)
			{ 
				frame++;
				if (frame >= 6) frame = 0;
			}
			else
			{
				frame--;
				if (frame < 0) frame = 5;
			}

		}
		
	}

	void UpgradeFriend::LevelUp(int upgradeType)
	{
		if (level != 3) level++; //We don't want to level past 3.
		
		switch (level) //Set the hitboxes of the sprite
		{
		case 1:
		{
			xOffset = 0;
			yOffset = 0;
			width = 39;
			height = 32;
			break;
		}
		case 2:
		{
			xOffset = 0;
			yOffset = 0;
			width = 55;
			height = 44;
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			printf("ERR: UpgradeFriend::LevelUp() upgraded to not expected value!");
			break;
		}
		}
		currentUpgrade = upgradeType;
	}
	
	void UpgradeFriend::Draw(Surface* screen)
	{
		switch (level)
		{
		case 1:
		{
			upgradeFriend1SPR.SetFrame(frame);
			upgradeFriend1SPR.Draw(screen, (int)x, (int)y);
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			printf("ERR: Uninitialized UpgradeFriend::Draw()!");
			break;
		}
		}
	}
}