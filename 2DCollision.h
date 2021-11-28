#pragma once
#include "Entity.h"

namespace Tmpl8{
	class Collision2D {
	public:
		Collision2D()
		{};
		static bool AABBOverlap(Entity* A, Entity* B);
		static bool didEntityHitTile(Entity* A);
		static bool isPositionOnDeadlyTile(int position[2]);
	};

	const int TILESIZE = 32; //Tilesize in pixels
}