#include "precomp.h" // include this first in every .cpp file

#include "game.h"
#include "SpriteDisplayer.h"
#include "RedEnemy.h"
#include "CircleEnemy.h"
#include "GreenMiniBossEnemy.h"
#include "MissleEnemy.h"
#include "OrangeMiniBossEnemy.h"
#include "TurretEnemy.h"
#include "UpgradeEnemy.h"
#include "WalkerEnemy.h"
#include "WhiteEnemy.h"
#include "YellowEnemy.h"

namespace Tmpl8
{
	enum { UP = -1, STOP, DOWN };
	enum { LEFT = -1, RIGHT = 1 };


	extern int requestHOR;
	extern int requestVER;
	extern bool bSelectorUp;
	extern bool bSelectorDown;
	extern bool bGoLeft;
	extern bool bGoRight;
	
	int SpriteNumber = 0;
	int SpriteFrame = 0;
	int SpriteX = SCRWIDTH / 2;
	int SpriteY = SCRHEIGHT / 2;
	int SpriteOffsetX = 0;
	int SpriteOffsetY = 0;
	int SpriteWidth = 0;
	int SpriteHeight = 0;
	int selected = 0;


	Sprite upgradeFriend1SPR2(new Surface("assets/UpgradeFriend1SPR.tga"), 12); //6 left, 6 right
	Sprite upgradeFriend2SPR2(new Surface("assets/UpgradeFriend2SPR.tga"), 12); //6 left, 6 right
	Sprite upgradeShotRedSPR2(new Surface("assets/UpgradeShotRedSPR.tga"), 16);
	Sprite upgradeShotRedBridgeSPR2(new Surface("assets/UpgradeShotRedBridgeSPR.tga"), 28);
	Sprite upgradeShotRedBridgeBridgeSPR2(new Surface("assets/UpgradeShotRedBridgeBridgeSPR.tga"), 20);

	int staters = 0;

	void SpriteDisplayer(Surface* screen)
	{
		char bufferText[100];


		switch (staters)
		{
		case 0:
		{
			if (!(SpriteFrame < 0))
				upgradeShotRedBridgeSPR2.SetFrame(SpriteFrame);
			upgradeShotRedBridgeSPR2.Draw(screen, SpriteX, SpriteY);
			if (SpriteFrame >= 14)
			{
				SpriteFrame = 0;
				staters++;
				SpriteY += 4;
			}
			if (SpriteFrame < 0) SpriteFrame = 13;
			break;
		}
		case 1:
		{
			if(!(SpriteFrame < 0))
				upgradeShotRedBridgeBridgeSPR2.SetFrame(SpriteFrame);
			upgradeShotRedBridgeBridgeSPR2.Draw(screen, SpriteX, SpriteY);
			if (SpriteFrame >= 10)
			{
				SpriteFrame = 0;
				staters++;
			}
			if (SpriteFrame < 0)
			{
				SpriteY -= 4;
				staters--;
				SpriteFrame = 13;
			}
			break;
		}
		case 2:
		{
			if (!(SpriteFrame < 0))
				upgradeShotRedSPR2.SetFrame(SpriteFrame);
			upgradeShotRedSPR2.Draw(screen, SpriteX, SpriteY);
			if (SpriteFrame >= 8) SpriteFrame = 0;
			if (SpriteFrame < 0)
			{
				SpriteFrame = 9;
				staters--;
			}
			break;
		}
		default:
			break;
		}

		///DISPLAY SPRITE (NOT GOOD)
		//AllSprites[SpriteNumber]->SetFrame(SpriteFrame);
		//AllSprites[SpriteNumber]->Draw(screen, SpriteX, SpriteY);

		///DISPLAY TEXT		
		int color = 0xffffff;
		int x = 10;
		int y = 0;
		for (int i = 0; i < 8; i++)
		{
			if (i == selected) {
				color = 0xffff00;
			}
			else
			{
				color = 0xffffff;
			}
			switch (i)
			{
			case 0: //WHICH SPRITE
			{
				y = 10;
				sprintf(bufferText, "Current Sprite: %i", SpriteNumber);
				break;
			}
			case 1:
			{
				y = 20;
				sprintf(bufferText, "Current Frame: %i", SpriteFrame);
				break;
			}
			case 2: //X of SPRITE
			{
				y = 30;
				sprintf(bufferText, "Sprite X: %i", SpriteX);

				break;
			}
			case 3: //Y of SPRITE
			{
				y = 40;
				sprintf(bufferText, "Sprite Y: %i", SpriteY);
				break;
			}
			case 4: //OFFSET X of SPRITE
			{
				y = 50;
				sprintf(bufferText, "Sprite OffsetX: %i", SpriteOffsetX);
				break;
			}
			case 5: //OFFSET Y of SPRITE
			{
				y = 60;
				sprintf(bufferText, "Sprite OffsetY: %i", SpriteOffsetY);
				break;
			}
			case 6: //WIDTH of SPRITE
			{
				y = 70;
				sprintf(bufferText, "Sprite Width: %i", SpriteWidth);
				break;
			}
			case 7: //HEIGHT of SPRITE
			{
				y = 80;
				sprintf(bufferText, "Sprite Height: %i", SpriteHeight);
				break;
			}
			default:
			{
				break;
			}
			}
			screen->Print(bufferText, x, y, color);
		}

		///DRAW HITBOX
		screen->Line(SpriteX - 5.0f, (float)SpriteY, SpriteX + 5.0f, (float)SpriteY, 0xff0000);
		screen->Line((float)SpriteX, SpriteY - 5.0f, (float)SpriteX, SpriteY + 5.0f, 0xff0000);
		screen->Box(SpriteOffsetX + SpriteX, SpriteOffsetY + SpriteY, SpriteOffsetX + SpriteX + SpriteWidth, SpriteOffsetY + SpriteY + SpriteHeight, 0x00B7EB);


		///CHANGE TEXT
		if (bSelectorUp)
		{
			if (selected < 7)
			{
				selected++;
			}
			else
			{
				selected = 0;
			}
			bSelectorUp = false;
		}
		if (bSelectorDown)
		{
			if (selected > 0)
			{
				selected--;
			}
			else
			{
				selected = 7;
			}
			bSelectorDown = false;
		}

		int n = 0;

		switch (selected)
		{
		case 0: //Sprite
		{
			n = SpriteNumber;
			break;
		}
		case 1: //Frame
		{
			n = SpriteFrame;
			break;
		}
		case 2: //X
		{
			n = SpriteX;
			break;
		}
		case 3: //Y
		{
			n = SpriteY;
			break;
		}
		case 4: //OffsetX
		{
			n = SpriteOffsetX;
			break;
		}
		case 5: //OffsetY
		{
			n = SpriteOffsetY;
			break;
		}
		case 6: //Width
		{
			n = SpriteWidth;
			break;
		}
		case 7: //Height
		{
			n = SpriteHeight;
			break;
		}
		default:
		{
			break;
		}
		}

		if (requestHOR == RIGHT)
		{
			n++;
		}
		if (requestHOR == LEFT)
		{
			n--;
		}
		if (bGoRight)
		{
			n++;
			bGoRight = false;
		}
		if (bGoLeft)
		{
			n--;
			bGoLeft = false;
		}

		switch (selected)
		{
		case 0: //Sprite
		{
			SpriteNumber = n;
			break;
		}
		case 1: //Frame
		{
			SpriteFrame = n;
			break;
		}
		case 2: //X
		{
			SpriteX = n;
			break;
		}
		case 3: //Y
		{
			SpriteY = n;
			break;
		}
		case 4: //OffsetX
		{
			SpriteOffsetX = n;
			break;
		}
		case 5: //OffsetY
		{
			SpriteOffsetY = n;
			break;
		}
		case 6: //Width
		{
			SpriteWidth = n;
			break;
		}
		case 7: //Height
		{
			SpriteHeight = n;
			break;
		}
		default:
		{
			break;
		}
		}

	}
}