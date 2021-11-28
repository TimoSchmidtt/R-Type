#pragma once
#include "enemy.h"
namespace Tmpl8
{
    class MissleEnemy :
        public Enemy
    {
    private:
        void ShootMissles(Entity* player);
        void MoveTowardsPosition(Entity* player);
        void DetermineSprite(Entity* player);
    public:
        MissleEnemy()
        {
            type = MISSLE_ENEMY;
            width = 64;
            height = 60;
            speed = 4;
            frame = 2;
            velocity[1] = 0;
        }
        void Update(float* deltaTime, Surface* screen); //Can't be called Update() otherwise we loop into parent Update()
        void Draw(Surface* screen);
        bool otherLeg = false;
        enum { MOVE = 0, SHOOT, POSTSHOOT};
    };

}
