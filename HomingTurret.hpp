//
//  HomingTurret.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-18.
//

// Class for the homing missile turret.

#ifndef HomingTurret_hpp
#define HomingTurret_hpp
#include "BadGuy.h"
#include "HomingLaser.hpp"
#include "BadLaser.hpp"
#include "Shot.hpp"
#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"

class HomingTurret: public BadGuy {
    public:
        HomingTurret();
        void move(SDL_Rect playerRect);
        void shoot(SDL_Rect playerRect, vector<Shot*>& badShots);
        void render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle);
        void setVelX();
        void setVelY();
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
        void setStartingXpos();
        void setStartingYpos();
        int getType();
        int getHp();
        MyTimer getShootTimer();
        MyTimer getSpawnTimer();
        bool getSpawned();
        
    private:
        bool isInit;
        bool spawned;
        int hp;
        MyTimer shootTimer;
        MyTimer spawnTimer;
};

#endif /* HomingTurret_hpp */
