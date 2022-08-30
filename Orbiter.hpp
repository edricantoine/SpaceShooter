//
//  Orbiter.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-19.
//

// Class for the Orbiter enemy.

#ifndef Orbiter_hpp
#define Orbiter_hpp

#include <stdio.h>
#include "BadGuy.h"
#include "BadLaser.hpp"
#include "HomingLaser.hpp"
#include "Shot.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"

#endif /* Orbiter_hpp */

class Orbiter: public BadGuy {
    public:
        Orbiter();
        void move(SDL_Rect playerRect);
        void shoot(SDL_Rect playerRect, vector<Shot*>& badShots);
        void render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle);
        void setVelX();
        void setVelY();
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
        void setStartingPos(SDL_Rect playerRect);
        int getType();
        int getHp();
    private:
        int hp;
        bool isInit;
        int angle;
        MyTimer shootTimer;
    
};
