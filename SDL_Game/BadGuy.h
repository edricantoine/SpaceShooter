//
//  BadGuy.h
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-24.
//

#ifndef BadGuy_h
#define BadGuy_h

#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "MyTimer.hpp"
#include "Shot.hpp"
#include "HomingLaser.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <vector>
#include <ctime>

// ABSTRACT class for all enemy units

using namespace std;

class BadGuy {
    public:
        BadGuy();
    // functions to inherit
        virtual ~BadGuy();
    // moves according to velocity
        virtual void move(SDL_Rect playerRect) = 0;
    // shoots projectile if applicable
        virtual void shoot(SDL_Rect playerRect, vector<Shot*>& badShots) = 0;
    // sets x-velocity and y-velocity
        virtual void setVelX() = 0;
        virtual void setVelY() = 0;
    // makes sprite disappear, sets isDead to true
        virtual void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) = 0;
    // renders w/ appropriate texture
        virtual void render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle) = 0;
    // which type of enemy: 0 = asteroid, 1 = straight shooter, 2 = homing turret, (more to be added later)
        virtual int getType() = 0;
    // getters
        bool getDead();
        SDL_Rect getRect();
        int getVelX();
        int getVelY();
        bool getHit();
        bool willDrop();
        int itemDrop();

    // what to do when hit
        void onHit();
    // setters handling item drops
        void setWillDropItem();
        void setItemToDrop();
            protected:
        SDL_Rect rectangle;
        int velX;
        int velY;
        bool isDead;
        bool isHit;
        MyTimer hitTimer;
    // Upon initialization, 1/8 chance for this to be true
        bool willDropItem;
    // 4 powerups, so rolls a random number from 1 to 5
    // 1 = SHIELD, 2 = SPREAD SHOT, 3 = PIERCING SHOT, 4 = EXTRA BATTERY, 5 = CHARGE SHOT
        int itemToDrop;
     
};

#endif /* BadGuy_h */
