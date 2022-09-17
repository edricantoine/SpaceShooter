//
//  Enemy.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-20.
//

#ifndef Enemy_hpp
#define Enemy_hpp
#include "BadGuy.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <vector>
#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "HomingLaser.hpp"
#include "Shot.hpp"

// Enemy class (for the bouncing asteroids) inheriting from BadGuy class

using namespace std;

class Enemy: public BadGuy {
    public:
        Enemy();
    // Moves according to velX and velY
        void move(SDL_Rect playerRect);
    // Renders with appropriate texture
        void render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle);
    // setters
        void setVelX();
        void setVelY();
    // sets isAlive to false, and makes enemy disappear
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
    // sets this asteroid's starting y position
        void setStartingYpos();
    // does nothing since the asteroids don't shoot
        void shoot(SDL_Rect playerRect, vector<Shot*>& badShots);
        int getType();
    
};

#endif /* Enemy_hpp */
