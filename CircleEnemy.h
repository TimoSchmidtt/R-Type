#pragma once
#include "enemy.h"
namespace Tmpl8
{
    class CircleEnemy :
        public Enemy
    {
    public:
        void Update(float* deltaTime, Surface* screen);
        void Draw(Surface* screen);
        void DetermineAngle();

        bool alive = false;
        bool head = false; //Are we the blue circle enemy?
        
    };

}