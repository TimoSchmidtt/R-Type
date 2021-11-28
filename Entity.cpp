#include "precomp.h" // include this first in every .cpp file
#include "Entity.h"

namespace Tmpl8
{
	Entity* allEntities[300];
	int Entity::totalActive = 0;

	Entity* Entity::GetEntityFromType(int type) //Gets the first iteration of that type. Useful for getting Camera and Player, since we only want one of those.
	{
		int n = allEntities[0]->totalActive;
		for (int i = 0; (i < sizeof(allEntities) / sizeof(Entity*)) && (i < n + i); i++)
		{
			if (allEntities[i] && allEntities[i]->bActive)
			{
				if (allEntities[i]->type == type)
				{
					return allEntities[i];
				}
			}
		}
		return nullptr;
	}

	void Entity::CreateEntity(Entity* entity) //Puts the entity into the first nullptr/inactive entity.
	{
		if (entity->x == -100 || entity->y == -100)
		{
			printf("Entity X or Y IS unitialized. Are you sure this should be happening?");
		}
		for (int i = 0; i < sizeof(allEntities) / sizeof(Entity*); i++)
		{
			if (!allEntities[i] || !allEntities[i]->bActive)
			{
				allEntities[i] = entity;
				allEntities[i]->bActive = true;
				allEntities[i]->totalActive++;
				break;
			}
		}
	}
}