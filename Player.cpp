#include "precomp.h"
#include "player.h"
#include "game.h"
#include "Camera.h"
#include "shot.h" //CreateShot()
#include "2DCollision.h"
#include "UpgradeFriend.h"

namespace Tmpl8
{
	extern int requestHOR;
	extern int requestVER;
	extern bool bRequestShot;
	extern bool bFiredShot;
	extern bool bRequestFriend;


	Sprite playerSPR(new Surface("assets/playerSPR.tga"), 10); //2 downward right, 1 right, 2 upward right, 2 upward left, 1 left, 2 downward left
	Sprite chargingSPR(new Surface("assets/chargingSPR.tga"), 16); //8 charge left, 8 charge right
	Sprite chargeBarSPR(new Surface("assets/ChargeBarSPR.tga"), 1); //1

	Sprite shot1SPR(new Surface("assets/shot1SPR.tga"), 6);
	Sprite chargeShot1SPR(new Surface("assets/chargeShot1SPR.tga"), 4);
	Sprite chargeShot2SPR(new Surface("assets/chargeShot2SPR.tga"), 4);
	Sprite chargeShot3SPR(new Surface("assets/chargeShot3SPR.tga"), 4);
	Sprite chargeShot4SPR(new Surface("assets/chargeShot4SPR.tga"), 4);
	Sprite chargeShot5SPR(new Surface("assets/chargeShot5SPR.tga"), 4);
	Sprite shotBridgeSPR(new Surface("assets/shotBridgeSPR.tga"), 8); //4 shotbridge left, 4 shotbridge right


	extern Entity* allEntities[300];

	enum { UP = -1, STOP, DOWN };
	enum { LEFT = -1, STOPS, RIGHT };

	
	
	void Player::HandlePlayerControls(float* deltaTime) //Everything related to moving and shooting
	{
		if (bActive)
		{
			if (requestHOR == LEFT && !(x <= 0))
			{
				velocity[0] = requestHOR * (float)speed;
			}
			if (requestHOR == RIGHT && !(x + width >= (SCRWIDTH)))
			{
				velocity[0] = requestHOR * (float)speed;
			}
			if (requestHOR == STOP)
			{
				velocity[0] = 0;
			}

			//Change Sprite based on direction
			if (requestVER == STOP)
			{
				velocity[1] = 0;
				if (sprite < 2)
				{
					sprite++;
				}
				else if (sprite > 2)
				{
					sprite--;
				}
			}		
			

			if (requestVER == UP)
			{
				if (sprite < 4)
				{
					sprite++;
				}
				if (y >= 0)
				{
					velocity[1] = requestVER * (float)speed;
				}
				else
				{
					velocity[1] = 0.0f;
				}
					
			}
			if (requestVER == DOWN)
			{
				if (sprite > 0)
				{
					sprite--;
				}

				if (!(y >= (SCRHEIGHT - height)))
				{
					velocity[1] = requestVER * (float)speed;
				}
			}
			if (bRequestShot) //Handles visuals
			{
				chargeTimer += *deltaTime;
				if (chargeTimer >= 50)
				{
					chargeFrame++;
					chargeTimer = 0.0f;
				}

				if (chargeFrame == 8) chargeFrame = 0;
			}
			else
			{
				chargeTimer = 0;
				chargeFrame = 0;
			}

			if (bRequestFriend)
			{
				Entity* ballFriend = Entity::GetEntityFromType(UPGRADE_FRIEND);
				if (ballFriend)
				{
					ballFriend->velocity[0] = 0.0f;
					ballFriend->velocity[1] = 0.0f;
					if (((UpgradeFriend*)ballFriend)->linked) 
					{
						ballFriend->state = ((UpgradeFriend*)ballFriend)->BOOST;
						
					}
					else if(ballFriend->state != ((UpgradeFriend*)ballFriend)->GOTO_PLAYER)
					{
						ballFriend->state = ((UpgradeFriend*)ballFriend)->GOTO_PLAYER;
					}
					else
					{
						ballFriend->state = ((UpgradeFriend*)ballFriend)->DEFAULT;
					}
				}
					
				bRequestFriend = false;
			}

		}
			

	}

	void Player::HandleCharging() //Logic for charging
	{
		if (bRequestShot)
		{
			if (chargeBar == 0)
			{
				Entity* ballFriend = Entity::GetEntityFromType(UPGRADE_FRIEND);
				if (ballFriend)
					((Enemy*)ballFriend)->bShoot = true;

				drawShotBridge = true;
				CreateShot(SHOT1 + chargeBar / 20);
			}
			if (chargeBar < 100) chargeBar++;
		}
		else if (chargeBar > 20) //we don't shoot the normal bullet twice
		{
			drawShotBridge = true;
			CreateShot(SHOT1 + chargeBar / 20);

			chargeBar = 0;
		}
		else chargeBar = 0;
	}

	void Player::CreateShot(int xType)
	{
		float xPosition = x + 45.0f;
		float yPosition = y + 4.0f;
		float xVelocity = 4.0f;
		
		shotBridgeFrame = 7;
		shotBridgeTimer = 0;
		Shot* shot = new Shot();
		
		shot->type = xType;
		shot->velocity[0] = xVelocity;
		shot->x = xPosition;
		shot->y = yPosition;

		shot->friendly = true;
			
		bool Shotpiercing = true;
		int ShotxOffset = 0;
		int ShotyOffset = 0;
		int Shotwidth = 0;
		int Shotheight = 0;
		int Shotdamage = 0;
		Sprite* Shotsprite = &playerSPR;

		switch (xType)
		{
			case SHOT1:
			{
				Shotpiercing = false;
				Shotdamage = 1;
				ShotxOffset = 0;
				ShotyOffset = 8;
				Shotwidth = 32;
				Shotheight = 8;
				Shotsprite = &shot1SPR;
				break;
			}
			case CHARGE1:
			{
				Shotdamage = 1;
				ShotxOffset = 4;
				ShotyOffset = 0;
				Shotwidth = 13;
				Shotheight = 12;
				Shotsprite = &chargeShot1SPR;
				break;
			}
			case CHARGE2:
			{
				Shotdamage = 1;
				ShotxOffset = 10;
				ShotyOffset = 0;
				Shotwidth = 23;
				Shotheight = 12;
				Shotsprite = &chargeShot2SPR;
				break;
			}
			case CHARGE3:
			{
				Shotdamage = 1;
				ShotxOffset = 17;
				ShotyOffset = 0;
				Shotwidth = 30;
				Shotheight = 15;
				Shotsprite = &chargeShot3SPR;
				break;
			}
			case CHARGE4:
			{
				Shotdamage = 1;
				ShotxOffset = 30;
				ShotyOffset = 0;
				Shotwidth = 32;
				Shotheight = 15;
				Shotsprite = &chargeShot4SPR;
				break;
			}
			case CHARGE5:
			{
				Shotdamage = 1;
				ShotxOffset = 35;
				ShotyOffset = 0;
				Shotwidth = 47;
				Shotheight = 15;
				Shotsprite = &chargeShot5SPR;
				break;
			}
			default:
			{
				printf("UNIMPLEMENTED Player::CreateShot()");
				break;
			}
		}
		shot->piercing = Shotpiercing;
		shot->damage = Shotdamage;
		shot->xOffset = ShotxOffset;
		shot->yOffset = ShotyOffset;
		shot->width = Shotwidth;
		shot->height = Shotheight;
		shot->sprite = Shotsprite;
		shot->playerShots++;
		
		Entity::CreateEntity(shot);
		return;
		
		
	}

	void Player::Update(float* deltaTime, Surface* screen)
	{
		switch (state)
		{
		case INTRO:
		{

			break;
		}
		case ACTIVE:
		{
			x += velocity[0];
			y += velocity[1];
			shotBridgeTimer += *deltaTime;
			HandlePlayerControls(deltaTime);
			HandleCharging();
			if (Collision2D::didEntityHitTile(this))
			{
				Die();
			}
			Draw(screen);
			break;
		}
		case DEAD:
		{

			break;
		}
		case POSTLEVEL:
		{

			break;
		}
		default:
			break;
		}
	}
		
	void Player::Draw(Surface* screen)
	{
		if (bActive && bDraw)
		{
			if (drawShotBridge)
			{
				if (shotBridgeTimer >= 50) //This should be under player.cpp.
				{
					shotBridgeTimer = 0;
					if (shotBridgeFrame > 3)
					{
						shotBridgeFrame--;
					}
				}
				if (shotBridgeFrame < 0)
				{
					shotBridgeFrame = 0;
					drawShotBridge = false;
				}
				shotBridgeSPR.SetFrame(shotBridgeFrame);
				if (shotBridgeFrame > 3 && chargeBar > 20)
				{
					shotBridgeSPR.Draw(screen, (int)x + 62, (int)y-8);
				}
			}


			playerSPR.SetFrame(sprite);
			playerSPR.Draw(screen, (int)x, (int)y);

			//Charge
			if (bRequestShot && chargeBar > 20) //If charging
			{
				chargingSPR.SetFrame(chargeFrame);
				chargingSPR.Draw(screen, (int)x + 60, (int)y);
			}
			//Draw chargeBar
			for (int i = 0; i < chargeBar; i++)
			{
				screen->Line(75, SCRHEIGHT - 30, ((float)(i + 1) * 5) + 75, SCRHEIGHT - 30, 0x0055ff);
			}
		}
	}


	void Player::Die()
	{
		//active = false;
		printf("DEAD");
	}
		
}