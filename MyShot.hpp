//
//  MyShot.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-28.
//

// ABSTRACT class for all projectiles the player can shoot.

#ifndef MyShot_hpp
#define MyShot_hpp

#include <stdio.h>
#include "MyTexture.hpp"
#include "Enemy.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

class MyShot {
    public:
        MyShot(MyTexture* t);
        virtual ~MyShot();
        virtual void move() = 0;
        virtual void render(SDL_Renderer** gRenderer);
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
        int getXvel();
        int getYvel();
        SDL_Rect getRect();
        bool getOnscreen();
    protected:
        SDL_Rect rectangle;
        int xvel;
        int yvel;
        bool onscreen;
        MyTexture* texture;
};

#endif /* MyShot_hpp */
