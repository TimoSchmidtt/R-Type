#include "precomp.h"
#include "MissleEnemy.h"
#include "shot.h"
#include "2DCollision.h"
#include "Camera.h"

namespace Tmpl8
{
	Sprite missleEnemySPR(new Surface("assets/MissleEnemySPR.tga"), 20); //6 left, 6 right, 3 up shoot leftward, 1 topleft, 1 topright, 3 up shoot rightward
	Sprite missleEnemyMissleSPR(new Surface("assets/MissleEnemyMissleSPR.tga"), 18); //18 degree
	
	void MissleEnemy::DetermineSprite(Entity* player) //THIS MATTERS LESS (not done yet)
	{		
		switch (state)
		{
		case MOVE:
		{
			if (velocity[0] < 0)
			{
				if (otherLeg)
				{
					if (frameTimer >= 50)
					{
						frame--;
						if (frame < 0)
						{
							frame = 2;
							otherLeg = false;
						}
					}
					//[2], 1, 0, [2]
				}
				else
				{
					if (frameTimer >= 50)
					{
						frame++;
						if (frame == 4)
						{
							frame = 2;
							otherLeg = true;
						}
					}
					//[2], 4, 3, [2]
				}
			}
			break;
		}
		case SHOOT:
		{
			frame = 15;
			break;
		}
		case POSTSHOOT:
		{
			break;
		}
		}
	}

	void MissleEnemy::MoveTowardsPosition(Entity* player)
	{
		if ((int)x > (int)(player->x + player->width) + 100)
		{
			velocity[0] = (float)-speed;
		}			
		else if ((int)x < (int)(player->x + player->width) + 100)
		{
			velocity[0] = (float)speed;
		}
	}
	
	void MissleEnemy::Update(float* deltaTime, Surface* screen)
	{
		frameTimer += *deltaTime;
		Entity* player = Entity::GetEntityFromType(PLAYER);
		Entity* camera = Entity::GetEntityFromType(CAMERA);
		
		if(((Camera*)camera)->move)
			x -= ((Camera*)camera)->speed; //make our movements based on the camera


		if (x + width < 0)
		{
			bActive = false; //Die but no player credit
		}

		DetermineSprite(player);

		switch (state)
		{
		case MOVE:
		{
			MoveTowardsPosition(player);
			if (!(Collision2D::didEntityHitTile(this)))
			{
				x += velocity[0];
				y += velocity[1];
			}
			int position[2] = { (int)x, (int)(y + height) + 1 };
			if (!(Collision2D::isPositionOnDeadlyTile(position)))
			{
				y += 2;
			}
			break;
		}
		case SHOOT:
		{
			ShootMissles(player);
			break;
		}
		case POSTSHOOT:
		{

			break;
		}
		default:
			break;
		}

		Draw(screen);
	}

	void MissleEnemy::Draw(Surface* screen)
	{
		missleEnemySPR.SetFrame(frame);
		missleEnemySPR.Draw(screen, (int)x, (int)y);
	}

	void MissleEnemy::ShootMissles(Entity* player)
	{
		Entity* missle = new Shot();
		missle->type = MISSLESHOT;

		missle->x = x;
		missle->y = y;
		missle->width = 29;
		missle->height = 25;
		((Shot*)missle)->friendly = false;



		((Shot*)missle)->velocity[0] = -.3f - ((rand() % 6) / 10.0f);
		((Shot*)missle)->velocity[1] = -6.0f - (rand() % 10) / 10.0f;
		((Shot*)missle)->sprite = &missleEnemyMissleSPR;
		Entity::CreateEntity(missle);

		state = POSTSHOOT;

		//7 missles
	}
}