#pragma once
#include "Enemy.h"

namespace Tmpl8
{
    class UpgradeFriend :
        public Enemy
    {
    private:
        bool front = false; //Are we to the front or the back of the player
        int level = 0; //What level we are
        int currentUpgrade = -1; //Current upgrade, initializes at -1 so we need an upgrade.
        void DetermineFrame(); //Change frame to the frame it should be.
        void Shoot();   //Shoot
        void ShootAlone(); //Shoot bullet as if we're unlinked (boring 1-2-3)
        void ShootUpgrade(); //Shoot bullet as if we're linked (upgrade-specific)
        void DetectStickToPlayer(Entity* player); //Detect if we are overlapping the player and initialize STAY_PLAYER.
        bool rotateUp = false; //Should we rotate up
    public:
        UpgradeFriend()
        {
            speed = 3;
            health = 999999;
            type = UPGRADE_FRIEND;
        };
        static Sprite UpgradeFriend::upgradeShotRedBridgeBridgeSPR;
        static Sprite UpgradeFriend::upgradeShotRedSPR;
        bool hurt = false; //Should we hurt enemies when we collide?
        bool linked = false; //Are we attached to the player?
        void LevelUp(int upgradeType); //Should be called to initialize the upgradeFriend.
        void Update(float* deltaTime, Surface* screen);
        void Draw(Surface* screen);
        enum { DEFAULT,  //Move towards players y and x with a delay
            GOTO_PLAYER, //Go towards the player
            STAY_PLAYER, //Stay linked to the player
            BOOST }; //Boost forward and hurt enemies
        
    };

}

