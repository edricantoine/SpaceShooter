//
//  Shot.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-26.
//

// ABSTRACT class for all enemy shots.

#ifndef Shot_hpp
#define Shot_hpp

#include <stdio.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class Shot {
    public:
        virtual ~Shot();
        virtual void move(SDL_Rect playerRect) = 0;
    // 0 = REGULAR BAD LASER, 1 = HOMING SHOT
        virtual int getType() = 0;
        void render(MyTexture* texture, SDL_Renderer** gRenderer);
        int getXvel();
        int getYvel();
        bool getOnscreen();
        SDL_Rect getRect();
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
        
    protected:
        SDL_Rect rectangle;
        int xvel;
        int yvel;
        bool onscreen;
};

#endif /* Shot_hpp */
