#include "precomp.h"
#include "WhiteEnemy.h"

namespace Tmpl8
{
	Sprite whiteEnemySPR(new Surface("assets/WhiteEnemySPR.tga"), 6); //3 left, 3 right
	void WhiteEnemy::Update(float* deltaTime, Surface* screen)
	{
		Entity* player = GetEntityFromType(PLAYER);
		//Take player position
		//move around
		//take player position again after some time

		//1 health
		
		Draw(screen);
	}

	void WhiteEnemy::Draw(Surface* screen)
	{
		//Keep looking back and forth
		whiteEnemySPR.SetFrame(frame);
		whiteEnemySPR.Draw(screen, (int)x, (int)y);
	}
}