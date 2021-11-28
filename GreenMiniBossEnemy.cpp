#include "precomp.h"

#include "GreenMiniBossEnemy.h"
namespace Tmpl8
{
	Sprite greenMiniBossSPR(new Surface("assets/GreenMiniBossSPR.tga"), 6); //3 left 3 right
	Sprite greenMiniBossBulletSPR(new Surface("assets/GreenMiniBossBulletSPR.tga"), 6); //3 left 3 right
	Sprite greenMiniBossBulletBridgeSPR(new Surface("assets/GreenMiniBossBulletBridgeSPR.tga"), 6); //3 left 3 right
	void GreenMiniBossEnemy::Update(float* deltaTime, Surface* screen)
	{
		//DO it :]
		Draw(screen);
	}

	void GreenMiniBossEnemy::Draw(Surface* screen)
	{
		greenMiniBossSPR.SetFrame(frame);
		greenMiniBossSPR.Draw(screen, (int)x, (int)y);
	}

}