#pragma once
#include "enemy.h"
namespace Tmpl8
{
    class OrangeMiniBossEnemy :
        public Enemy
    {
    public:
        void Update(float* deltaTime, Surface* screen); //Can't be called Update() otherwise we loop into parent Update()
        void Draw(Surface* screen);
    };
}
