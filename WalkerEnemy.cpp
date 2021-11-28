#include "precomp.h"
#include "WalkerEnemy.h"
#include "2DCollision.h"

namespace Tmpl8
{
	Sprite walkerEnemySPR(new Surface("assets/WalkerEnemySPR.tga"), 12); //3 walk left, 3 walk right, 3 jump left, 3 jump right

	enum states { WALKING = 0, AIRBORNE = 1 };

	void WalkerEnemy::DetermineGround()
	{
		if (Collision2D::didEntityHitTile(this))
		{
			switch (state)
			{
			case WALKING:
			{
				int position[2] = { (int)x, (int)(y + height) - 3 };
				if (!walkLeft)
				{
					position[0] = (int)(x + width);
				}

				if (Collision2D::isPositionOnDeadlyTile(position))
				{
					frame = 3;
					frameTimer = 251;
					walkLeft = !walkLeft;
				}
				break;
			}
			case AIRBORNE:
			{
				frame = 1 + 2 * (int)!walkLeft;
				break;
			}
			default:
				break;
			}
			state = WALKING;
		}
		else
		{
			if (state == WALKING)
				frame = 9 - 2 * (int)walkLeft;
			state = AIRBORNE;

		}
	}

	void WalkerEnemy::ChangeSpriteFrame(float* deltaTime)
	{
		frameTimer += *deltaTime;
		if (state == WALKING)
		{
			if (frameTimer >= 200)
			{
				frameTimer = 0;
				if (walkLeft)
				{
					if (frame > 2) frame = 2;
					if (frame < 0) frame = 0;
					if (frame == 2 || frame == 0) otherLeg = !otherLeg;

					if (otherLeg)
					{
						frame++;
					}
					else
					{
						frame--;
					}
				}
				else
				{
					if (frame < 3) frame = 3;
					if (frame > 5) frame = 5;
					if (frame == 3 || frame == 5) otherLeg = !otherLeg;
					if (otherLeg)
					{
						frame++;
					}
					else
					{
						frame--;
					}
				}
					
			}
		}
		else if (state == AIRBORNE)
		{
			if (frameTimer >= 200)
			{
				frameTimer = 0;
				if (walkLeft)
				{
					if (frame < 7) frame = 7;
					if (frame > 8) frame = 8;
					if (frame == 7 || frame == 8) otherLeg = !otherLeg;
					if (otherLeg)
						frame++;
					else
						frame--;
				}
				else
				{
					if (frame < 9) frame = 9;
					if (frame > 10) frame = 10;
					if (frame == 9 || frame == 10) otherLeg = !otherLeg;
					if (otherLeg)
						frame++;
					else
						frame--;
				}

			}
		}
	}

	void WalkerEnemy::Update(float* deltaTime, Surface* screen)
	{
		switch (state)
		{
			case WALKING:
			{
				if (walkLeft)
					x -= velocity[0];
				else
					x += velocity[0];
				break;
			}
			case AIRBORNE:
			{
				y += velocity[1];
				break;
			}
			default:
			{
				break;
			}
		}

		if (bShoot)
			NormalShootAtPlayer();

		DetermineGround();

		ChangeSpriteFrame(deltaTime);
		Draw(screen);
	}

	void WalkerEnemy::Draw(Surface* screen)
	{
		walkerEnemySPR.SetFrame(frame);
		walkerEnemySPR.Draw(screen, (int)x, (int)y);
	}
}