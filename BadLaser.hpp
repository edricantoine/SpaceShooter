//
//  BadLaser.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-10.
//

#ifndef BadLaser_hpp
#define BadLaser_hpp

#include <stdio.h>
#include "MyTexture.hpp"
#include "Shot.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

// Class representing a laser the enemy can shoot

class BadLaser: public Shot{
    public:
        // see GoodLaser for a lot of these explanations
        // Constructor now takes boolean saying whether this laser is moving forwards or backwards
        BadLaser(int xpos, int ypos, bool forward);
        void move(SDL_Rect playerRect);
        void render(MyTexture* laserTexture, SDL_Renderer** gRenderer);
        int getXvel();
        int getType();
        int getYvel();
        bool getOnscreen();
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
        SDL_Rect getRect();

};

#endif /* BadLaser_hpp */
