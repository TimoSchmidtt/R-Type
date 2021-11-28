#include "precomp.h"
#include "UpgradeEnemy.h"
namespace Tmpl8
{
	Sprite upgradeEnemySPR(new Surface("assets/UpgradeEnemySPR.tga"), 6); //1 fly, 1 land, 3 walk, 1 jump from walk
	void UpgradeEnemy::Update(float* deltaTime, Surface* screen)
	{
		//Fly sine-ish, if land, walk, if end of walk, jump to fly
		//1 health
		Draw(screen);
	}

	void UpgradeEnemy::Draw(Surface* screen)
	{
		upgradeEnemySPR.SetFrame(frame);
		upgradeEnemySPR.Draw(screen, (int)x, (int)y);
	}
}