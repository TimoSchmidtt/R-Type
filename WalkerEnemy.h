#pragma once
#include "enemy.h"
namespace Tmpl8
{
    class WalkerEnemy :
        public Enemy
    {
    public:
        WalkerEnemy()
        {
            type = WALKER_ENEMY;
            frame = 0;
            width = 64;
            height = 64;
            health = 1;
            velocity[0] = 2;
            velocity[1] = 2;
        };
        void Update(float* deltaTime, Surface* screen); //Can't be called Update() otherwise we loop into parent Update()
        void Draw(Surface* screen);
        bool walkLeft = true;
        bool otherLeg = false;
    private:
        void ChangeSpriteFrame(float* deltaTime);
        void DetermineGround();
    };


    
}