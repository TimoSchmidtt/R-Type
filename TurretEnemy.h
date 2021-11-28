#pragma once
#include "enemy.h"
namespace Tmpl8
{
    class TurretEnemy :
        public Enemy
    {
    private:
        void DetermineSpriteFrame(Entity* player);
    public:
        TurretEnemy()
        {
            type = TURRET_ENEMY;
            health = 1;
            width = 32;
            height = 30;
        }
        void Update(float* deltaTime, Surface* screen); //Can't be called Update() otherwise we loop into parent Update()
        void Draw(Surface* screen);
        enum { FLOOR = 0, CEILING };
    };
}
