#include "precomp.h"
#include "Spline.h"
#include <vector>

namespace Tmpl8
{
	struct Coordinates2D {
		float x;
		float y;
	};

	struct sSpline
	{
		Coordinates2D points[10];
		Coordinates2D getSplinePoint(float t, bool looped);
		Coordinates2D getSplineGradient(float t, bool looped);
	};

	sSpline path;
	sSpline boss;
	float fMarker = 0.0f;
	int selectedPoint = 0;

	extern int requestHOR; //-1 = left, +1 = right
	extern int requestVER; //-1 = up, +1 = down
	extern bool bRequestShot; //Do we want to shoot?
	extern bool bFiredShot; //Have we shot?
	extern bool bSelectorUp; //LSHIFT
	extern bool bSelectorDown; //RSHIFT
	extern bool bGoLeft; //LARROW
	extern bool bGoRight; //RARROW


	void SplineInit()
	{
		//path = { { 50, 175 },{ 150, 175 } ,{ 250, 175 } ,{ 350, 175 } ,{ 450, 175 },{ 550, 175 },{ 650, 175 } };

		for (int i = 0; i < 10; i++)
			path.points[i] = { 100.0f * sinf((float)i / 10.0f * 3.14159f * 2.0f) + SCRWIDTH / 2,
				100.0f * cosf((float)i / 10.0f * 3.14159f * 2.0f) + SCRHEIGHT / 2, };
	}

	Coordinates2D sSpline::getSplinePoint(float t, bool looped)
	{
		int p0, p1, p2, p3;
		if (!looped)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p2 + 1;
			p0 = p1 - 1;
		}
		else
		{
			p1 = (int)t;
			p2 = (p1 + 1) % (sizeof(points)/sizeof(Coordinates2D));
			p3 = (p2 + 1) % (sizeof(points)/sizeof(Coordinates2D));
			p0 = p1 >= 1 ? p1 - 1 : (sizeof(points)/sizeof(Coordinates2D)) - 1;
		}

		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -ttt + 2.0f * tt - t;
		float q2 = 3.0f * ttt - 5.0f * tt + 2.0f;
		float q3 = -3.0f * ttt + 4.0f * tt + t;
		float q4 = ttt - tt;

		float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
		float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

		return { tx, ty };
	}

	Coordinates2D sSpline::getSplineGradient(float t, bool looped)
	{
		int p0, p1, p2, p3;
		if (!looped)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p2 + 1;
			p0 = p1 - 1;
		}
		else
		{
			p1 = (int)t;
			p2 = (p1 + 1) % (sizeof(points)/sizeof(Coordinates2D));
			p3 = (p2 + 1) % (sizeof(points)/sizeof(Coordinates2D));
			p0 = p1 >= 1 ? p1 - 1 : (sizeof(points)/sizeof(Coordinates2D)) - 1;
		}

		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -3.0f * tt + 4.0f * t - 1;
		float q2 = 9.0f * tt - 10.0f * t;
		float q3 = -9.0f * tt + 8.0f * t + 1.0f;
		float q4 = 3.0f* tt - 2.0f * t;

		float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
		float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

		return { tx, ty };
	}


	void SplineUpdate(float* deltaTime, Surface* screen)
	{
		if (bGoLeft)
		{
			bGoLeft = false;
			selectedPoint--;


			if (selectedPoint < 0)
				selectedPoint = sizeof(path.points)/sizeof(Coordinates2D);
				
		}
		if (bGoRight)
		{
			bGoRight = false;
			selectedPoint++;

			if (selectedPoint > (sizeof(path.points)/sizeof(Coordinates2D)))
				selectedPoint = 0;
		}



		//Draw Spline
		for (float t = 0.0f; t < (float)(sizeof(boss.points)/sizeof(Coordinates2D)); t += 0.0001f)
		{
			Coordinates2D pos = path.getSplinePoint(t, true);
			screen->Plot((int)pos.x, (int)pos.y, 0xffffff);
			pos = boss.getSplinePoint(t, true);
			screen->Plot((int)pos.x, (int)pos.y, 0xff);
		}

		//Draw boxes
		for (int i = 0; i < (sizeof(path.points)/sizeof(Coordinates2D)); i++)
		{
			int color = 0xff0000;
			if (selectedPoint == i)
			{
				path.points[i].x += requestHOR * 5.0f;
				path.points[i].y += requestVER * 5.0f;
				color = 0xffff00;
			}
			screen->Box((int)path.points[i].x, (int)path.points[i].y, (int)path.points[i].x + 5, (int)path.points[i].y + 5, color);
		}


		//Draw agent
		
		Coordinates2D agent = path.getSplinePoint(fMarker, true);
		Coordinates2D corner = { SCRWIDTH, SCRHEIGHT };

		boss.points[0] = { agent.x, agent.y };
		boss.points[1] = { agent.x + 10, agent.y + 10 };
		for(int i = 1; i < 10; i++)
			boss.points[i] = { SCRWIDTH, SCRHEIGHT };
		

		//D2



		if (bSelectorUp)
		{
			fMarker += 0.05f;
		}
		if (bSelectorDown)
		{
			fMarker -= 0.05f;
		}

		if (fMarker >= (float)(sizeof(path.points)/sizeof(Coordinates2D)))
			fMarker -= (float)(sizeof(path.points)/sizeof(Coordinates2D));

		if (fMarker < 0.0f)
			fMarker += (float)(sizeof(path.points)/sizeof(Coordinates2D));

	}
}