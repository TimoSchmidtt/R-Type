#include "precomp.h"
#include "OrangeMiniBossEnemy.h"
namespace Tmpl8
{
	Sprite orangeMiniBossSPR(new Surface("assets/OrangeMiniBossSPR.tga"), 16); //5 left, 5 right, 3 fly left, 3 fly right
	Sprite orangeMiniBossBulletSPR(new Surface("assets/OrangeMiniBossBulletSPR.tga"), 2); //left, right
	Sprite orangeMiniBossMissleSPR(new Surface("assets/OrangeMiniBossMissleSPR.tga"), 16); //16 degree
	void OrangeMiniBossEnemy::Update(float* deltaTime, Surface* screen)
	{
		//DO it :]
		Draw(screen);
	}

	void OrangeMiniBossEnemy::Draw(Surface* screen)
	{
		orangeMiniBossSPR.SetFrame(frame);
		orangeMiniBossSPR.Draw(screen, (int)x, (int)y);
	}
}
