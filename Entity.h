#pragma once
#include "surface.h"

namespace Tmpl8 {

	class Entity {
	public:
		Entity()
		{
			x = -100; //Initialize out of bounds so we can call errors
			y = -100; //Initialize out of bounds so we can call errors
		};
		virtual void Update(float* deltaTime, Surface* screen) {
			for (int i = 0; i < 99; i++) printf("ENTITY UPDATE() CALL: BIG TROUBLE!!!\n");
			return;
		}
		virtual void TakeDamage(int amount){
			for (int i = 0; i < 99; i++) printf("ENTITY TAKEDAMAGE() CALL: BIG TROUBLE!!!\n");
			return;
		}
		static Entity* GetEntityFromType(int type); //Returns the first Entity inside allEntities[i] of this type
		static void CreateEntity(Entity* entity); //Puts this entity into allEntities, makes it active and updates totalActive.
		static int totalActive; //How many entities are alive

		bool bUnhittable = false; //Can we be hit?
		bool bActive = false; //Are we currently active?
		bool bDraw = true; //Should we be drawn?
		float x = 0; //X Position
		float y = 0; //Y Position
		int xOffset = 0; //Sprite X offset
		int yOffset = 0; //Sprite Y offset
		int width = 0; //Sprite width
		int height = 0; //Sprite Height
		int type = 0;
		int state = 0; //Current state
		vec2 velocity = { 0, 0 };
	};
	enum ENTITYTYPES {
		//General entities
		PLAYER = 1, CAMERA, RED_ENEMY, CIRCLE_ENEMY, GREEN_MINIBOSS_ENEMY, MISSLE_ENEMY, ORANGE_MINIBOSS_ENEMY,
		TURRET_ENEMY, UPGRADE_ENEMY, WALKER_ENEMY, WHITE_ENEMY, YELLOW_ENEMY, UPGRADE_FRIEND,
		//Friendly shots
		SHOT1, CHARGE1, CHARGE2, CHARGE3, CHARGE4, CHARGE5, UPGRADEFRIENDSHOT, 
		//Unfriendly shots
		ENEMYSHOT, MISSLESHOT,
		//Upgrade Types (dropped things)
		BLUE_UPGRADE, RED_UPGRADE, YELLOW_UPGRADE, MISSLE_UPGRADE, BALL_UPGRADE, 
		//Upgrade Shots
		RED_UPGRADE_SHOT, RED_UPGRADE_BRIDGE, RED_UPGRADE_BRIDGE_BRIDGE
	};

}