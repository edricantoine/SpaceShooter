//
//  PowerUp.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-23.
//

// ABSTRACT class for Powerups

#ifndef PowerUp_hpp
#define PowerUp_hpp

#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "MyTimer.hpp"
#include "HomingLaser.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <stdio.h>

using namespace std;

class PowerUp {
    public:
        PowerUp(MyTexture* t, int xpos, int ypos);
        virtual ~PowerUp();
        // moves like an Asteroid enemy
        void move();
        // renders and kills like any enemy
        void render(SDL_Renderer** gRenderer);
        //getters & setters
        MyTexture* getTexture();
        int getVelX();
        int getVelY();
        SDL_Rect getRect();
        MyTimer getTimer();
        bool getActive();
        void setVelX();
        void setVelY();
        // effect this item will have on the player upon being touched
    // ALSO DEACTIVATES THIS POWERUP.
        virtual void takeEffect(Player& p) = 0;
    protected:
        // texture this powerup will use
        MyTexture* texture;
        // x and y velocity
        int velX;
        int velY;
        // rectangle for sprite
        SDL_Rect rectangle;
        // timer controlling how long this powerup is onscreen for
        MyTimer activeTimer;
        // whether powerup is active
        bool isActive;
};

#endif /* PowerUp_hpp */
