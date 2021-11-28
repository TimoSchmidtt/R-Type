#include "precomp.h" // include this first in every .cpp file

#include "2DCollision.h"
#include "game.h"
#include "player.h"
#include "star.h"
#include "shot.h"
#include "enemy.h"
#include "Camera.h"
#include "SpriteDisplayer.h"
#include "MissleEnemy.h"
#include "YellowEnemy.h"
#include "EnemyPlacer.h"
#include "Spline.h"
#include "UpgradeFriend.h"

namespace Tmpl8
{
	int requestHOR; //-1 = left, +1 = right
	int requestVER; //-1 = up, +1 = down
	bool bRequestShot; //Do we want to shoot?
	bool bFiredShot; //Have we shot?
	bool bRequestFriend; //Do we want upgradefriend?
	bool bSelectorUp; //LSHIFT
	bool bSelectorDown; //RSHIFT
	bool bGoLeft; //LARROW
	bool bGoRight; //RARROW

	extern Entity* allEntities[300];

	enum { UP = -1, STOP, DOWN };
	enum { LEFT = -1, RIGHT = 1};
	
	Surface tiles("assets/nc2tiles.png");
	Surface level1Tiles("assets/level1tiles.png");

	extern int level1Map[20][300];


	int keyDown;
	int keyUp;
	Entity* camera;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		SplineInit();
		
		camera = new Camera();
		((Camera*)camera)->speed = 2;
		((Camera*)camera)->move = true;
		Entity::CreateEntity(camera);

		Entity::CreateEntity(new Player());	

		Entity* upgradeFriend = new UpgradeFriend();
		upgradeFriend->x = -30;
		upgradeFriend->y = SCRHEIGHT / 2;
		upgradeFriend->state = ((UpgradeFriend*)upgradeFriend)->DEFAULT;
		((UpgradeFriend*)upgradeFriend)->LevelUp(BLUE_UPGRADE);
		Entity::CreateEntity(upgradeFriend);
	}
	
	

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	void Game::KeyDown(int key) {
		
		key += 93; //Otherwise SDLK_[X] won't work.
		keyDown = key;
		switch (key) {
		case SDLK_q:
		{
			bRequestFriend = true;
			break;
		}
		case SDLK_a: //A
		{
			requestHOR = LEFT;
			break;
		}
		case SDLK_d: //D
		{
			requestHOR = RIGHT;
			break;
		}
		case SDLK_w: //W
		{
			requestVER = UP;
			break;
		}
		case SDLK_s: //S
		{
			requestVER = DOWN;
			break;
		}
		case SDLK_z: 
		{
			bRequestShot = true;
			break;
		}
		case 318: //LSHIFT
		{
			bSelectorUp = true;
			break;
		}
		case 322: //RSHIFT
		{
			bSelectorDown = true;
			break;
		}
		case 173: //LEFT
		{
			bGoLeft = true;
			break;
		}
		case 172: //RIGHT
		{
			bGoRight = true;
			break;
		}
		default:
		{
			//Do Nothing
		}
		}
	}

	void Game::KeyUp(int key) {
		key += 93; //Otherwise SDLK_[X] won't work.
		switch (key) {
		case SDLK_a: //A
		{
			requestHOR = STOP;
			break;
		}
		case SDLK_d: //D
		{
			requestHOR = STOP;
			break;
		}
		case SDLK_w: //W 
		{
			requestVER = STOP;
			break;
		}
		case SDLK_s: //S
		{
			requestVER = STOP;
			break;
		}
		case SDLK_z: {
			bRequestShot = false;
			bFiredShot = false;
			break;
		}
		case 318: //LSHIFT
		{
			bSelectorUp = false;
			break;
		}
		case 322: //RSHIFT
		{
			bSelectorDown = false;
			break;
		}
		default:
		{
			//Do Nothing
			break;
		}
		}
	}

	void DrawTiles(Surface* screen, int tileSheetWidth, int tilePerY)
	{
		int x0 = (int)camera->x / TILESIZE;
		int y0 = (int)camera->y / TILESIZE;
		int x1 = (int)(camera->x + SCRWIDTH) / TILESIZE;
		int y1 = (int)(camera->y + SCRHEIGHT) / TILESIZE;
		x1++; //Make sure we draw the next tile too that technically isn't on screen yet (so we don't have cut-off)

		if (x1 > 255) x1 = 300; //Tilemap protection
		if (y1 > 20) y1 = 20;	//Tilemap protection
		if (x0 < 0) x0 = 0;
		if (y0 < 0) y0 = 0;

		for (int y = y0; y < y1; y++)
		{
			for (int x = x0; x < x1; x++)
			{
				int t = level1Map[y][x];
				if (t == 0) continue; //Don't draw 0

				Pixel* src = level1Tiles.GetBuffer() +
					(t % tilePerY) * TILESIZE +
					((t / tilePerY) * TILESIZE) * tileSheetWidth;

				Pixel* dst = screen->GetBuffer() +
					x * TILESIZE - (int)camera->x + //Camera (so we) go right, tiles go left.
					y * TILESIZE * SCRWIDTH - SCRWIDTH * (int)camera->y; //We go up, tiles go down.
				for (int i = 0; i < TILESIZE; i++)
				{
					for (int j = 0; j < TILESIZE; j++)
					{
						//This if() protects against tile wrap
						if (((x * TILESIZE + (j - (int)camera->x)) > 0) &&
							((x * TILESIZE + (j - (int)camera->x)) < SCRWIDTH))
							dst[j] = src[j];

					}
					src += tileSheetWidth, dst += SCRWIDTH;
				}
			}
		}
	}

	void DrawDebug(Surface* screen, bool drawBoxes, bool drawVelocityLines)
	{
		int n = allEntities[0]->totalActive;
		int color = 0xffffff;
		for (int i = 0; (i < sizeof(allEntities) / sizeof(Entity*)) && (i < n + i); i++)
		{
			if (allEntities[i] && allEntities[i]->bActive)
			{
				

				if (drawBoxes)
				{
					int position1[2] = { (int)(allEntities[i]->x + allEntities[i]->xOffset), (int)(allEntities[i]->y + allEntities[i]->yOffset) };
					int position4[2] = { position1[0] + allEntities[i]->width, position1[1] + allEntities[i]->height }; //Bottom right

					screen->Box(position1[0],
						position1[1],
						position4[0],
						position4[1], 0xffffff);
				}
					
				n--;
				if (drawVelocityLines)
				{
					const int velocityLineColor = 0xff0000; //Red
					const int velocityMultiplier = 15; //Shows a bigger line than it actually moves (because it moves like .1 pixel to the left sometimes)
					screen->Line(allEntities[i]->xOffset + allEntities[i]->x + allEntities[i]->width / 2, allEntities[i]->yOffset + allEntities[i]->y + allEntities[i]->height / 2, allEntities[i]->xOffset + allEntities[i]->x + allEntities[i]->width / 2 + allEntities[i]->velocity[0] * velocityMultiplier, allEntities[i]->yOffset + allEntities[i]->y + allEntities[i]->height / 2 + allEntities[i]->velocity[1] * velocityMultiplier, velocityLineColor);

				}
			}
		}

	}
	
	int game_state = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// ----DO NOT MOVE UNLESS CERTAIN THAT YOU WANT THINGS TO BE DRAWN UNDER THESE------------------------------------------------------------
		screen->Clear(0);
		//*
		// ----DO NOT MOVE UNLESS CERTAIN THAT YOU WANT THINGS TO BE DRAWN UNDER THESE------------------------------------------------------------
		/*
		switch (game_state)
		{
			case TITLE_SCREEN:
			{
				//Placeholder title screen
				screen->Box(10, 10, 500, 500, 0xff00ff);
				screen->Print("r-type", 245, 245, 0xf3e2de);

				//Nothing gets updated
				if (bRequestShot) //When press z
				{
					game_state = PLAYING;
					bRequestShot = false;
				}	
				break;
			}
			case PLAYING:
			{
				DrawTiles(screen, 448 * 2, 28);

				int n = allEntities[0]->totalActive;
				printf("%i\n", n);
				for (int i = 0; (i < sizeof(allEntities) / sizeof(Entity*)) && (i < n + i); i++)
				{
					if (allEntities[i] && allEntities[i]->bActive)
					{
						allEntities[i]->Update(&deltaTime, screen);
						n--;
					}
				}


				if (false) //If die
				{
					game_state = CONTINUE;
				}
				break;
			}
			case CONTINUE:
			{
				if (true) //If we continue
				{
					game_state = PLAYING;
				}
				else
				{
					game_state = TITLE_SCREEN;
				}
				break;
			}
			default:
			{
				break;
			}
		}


		*/

		//*

		//*
		
		//*/
		SplineUpdate(&deltaTime, screen);
				

		//*
		
		//*/

		//EnemyPlacer(screen);
		//SpriteDisplayer(screen);
	}
};