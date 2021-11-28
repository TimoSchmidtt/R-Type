#include "precomp.h"
#include "EnemyPlacer.h"
#include "game.h"
#include "star.h"
#include "Camera.h"


//------------Enemy Types (Stage 1)--------------------//
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
//------------Enemy Types (Stage 2)-------------------//

namespace Tmpl8
{
	extern bool bSelectorUp;
	extern bool bSelectorDown;
	extern bool bGoLeft;
	extern bool bGoRight;
	extern bool requestShot;
	extern int requestHOR;
	extern int requestVER;

	extern Entity* allEntities[300];
	Star cursor;
	int state = 0;

	Surface level1EnemyPlacer("assets/level1EnemiesTEST.tga");
	Surface test(1, 1);

	void EnemyPlacer(Surface* screen)
	{
		Entity* camera = Entity::GetEntityFromType(CAMERA);
		if (!camera) return;
		/*
		[ENEMY] [IF APPLICABLE: version [NUM] ([DIRECTIONS MOVEMENT (BASED ON TIME, NOT POSITION)])]: [COLOR] 
		
		RedEnemy: 0xff0000
		YellowEnemy version 1 (^V^): 0xffff00 
		YellowEnemy version 2 (V^V^V): 0xffff01
		YellowEnemy version 3 (V<): 0xffff02
		WalkerEnemy: 0x7f0000
		
		
		
		*/
		int x = (int)(camera->x + SCRWIDTH);
		for (int y = 0; y < 240; y++)
		{
			Pixel* src = level1EnemyPlacer.GetBuffer() +
				x +
				y * 4210;
			if (*src != 0xffffffff)
				printf("x: %i, y: %i, color: %x\n", x, y, *src);
			*src &= 0xffffff;
			switch (*src)
			{
			case 0xff0000:
			{
				Entity* enemy = new RedEnemy();
				enemy->x = (float)x;
				enemy->y = (float)y;
				Entity::CreateEntity(enemy);
				break;
			}
			case 0xffff01:
			{
				Entity* enemy = new YellowEnemy();
				enemy->x = (float)x;
				enemy->y = (float)y;
				enemy->state = ((YellowEnemy*)enemy)->ZIG_ZAG;
				Entity::CreateEntity(enemy);
				break;
			}
			default:
				break;
			}
		}

		level1EnemyPlacer.Plot(0, 0, 0);
				


		
		/*
		for (int a = 0; a <= 5; a++)
		{
			if (camera->x == 857 + 15 * a)
			{
				for(int i = 0; i < sizeof(allEntities)/sizeof(Entity*); i++)
				{ 
					if (!allEntities[i] || !allEntities[i]->active)
					{
						allEntities[i] = new YellowEnemy();
						allEntities[i]->type = YELLOW_ENEMY;
						allEntities[i]->active = true;
						allEntities[i]->totalActive++;
						allEntities[i]->x = SCRWIDTH;
						allEntities[i]->y = SCRHEIGHT / 2;
						((YellowEnemy*)allEntities[i])->pivotPoint[1] = allEntities[i]->y;
						((YellowEnemy*)allEntities[i])->steps = 3;
						((YellowEnemy*)allEntities[i])->degrees = 180;
						((YellowEnemy*)allEntities[i])->radius = 30;
						((YellowEnemy*)allEntities[i])->state = 1;
						break;
					}
				}
			}

		}
		*/
		


		if (bSelectorUp)
		{
			camera->x += 32;
		}
		if (bSelectorDown)
		{
			camera->x -= 32;
		}

		cursor.x += requestHOR * 2; //AD
		cursor.y += requestVER; //WS

		if (bGoLeft) //left arrow
		{
			cursor.x--;
			bGoLeft = false;
		}
		if (bGoRight)
		{
			cursor.x++;
			bGoRight = false;
		}


		char bufferText[100];
		sprintf(bufferText, "X: %f, Y: %f", (float)cursor.x + (float)camera->x, (float)cursor.y + (float)camera->y);
		screen->Line(cursor.x - 5, cursor.y, cursor.x + 5, cursor.y, 0xff0000);
		screen->Line(cursor.x, cursor.y - 5, cursor.x, cursor.y + 5, 0xff0000);
		screen->Print(bufferText, 50, 50, 0xffffff);

		
		//place dem enemies!
	}
}