#include "precomp.h"
#include "Enemy.h"
#include "shot.h" //NormalShootAtPlayer()


namespace Tmpl8
{
	extern int requestHOR;
	extern int requestVER;

	extern Entity* allEntities[300];

	Sprite defaultEnemyShot(new Surface("assets/defaultshot.tga"), 8);
	bool stop = false;

	void Enemy::NormalShootAtPlayer()
	{
		Entity* player = Entity::GetEntityFromType(PLAYER);

		if (!player) //Make sure we actually find a player
			return;

		//shoot = false; //We have shot succesfully :]

		float playerMiddle[2] = { (player->x + player->xOffset + (player->width / 2)), (player->y + player->yOffset + (player->height / 2)) };
		float enemyMiddle[2] = { (x + xOffset + width / 2), (y + yOffset + height / 2) };

		Entity* shot = new Shot();
		((Shot*)shot)->friendly = false;
		
		shot->x = enemyMiddle[0] - xOffset;
		shot->y = enemyMiddle[1] - yOffset;
		
		shot->type = ENEMYSHOT;
		shot->xOffset = 14;
		shot->yOffset = 10;
		shot->width = 14;
		shot->height = 12;

		((Shot*)shot)->sprite = &defaultEnemyShot;
		((Shot*)shot)->speed = 4;
		
		float b = playerMiddle[0] - enemyMiddle[0];
		float h = playerMiddle[1] - enemyMiddle[1];
		float l = fabsf(b);
		if (fabsf(h) > l) l = fabsf(h);
		float dx = b / l;
		float dy = h / l;

		((Shot*)shot)->velocity[0] = dx * ((Shot*)shot)->speed;
		((Shot*)shot)->velocity[1] = dy * ((Shot*)shot)->speed;

		Entity::CreateEntity(shot);

	}

	void Enemy::TakeDamage(int amount)
	{
		health -= amount;
		if(health <= 0)
			Die();
	}

	void Enemy::Die()
	{
		bActive = false;
		totalActive--;
	}

}