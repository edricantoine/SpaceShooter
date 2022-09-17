//
//  MaxChargeLaser.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-09-03.
//

#ifndef MaxChargeLaser_hpp
#define MaxChargeLaser_hpp

#include <stdio.h>
#include "MyTexture.hpp"
#include "Enemy.hpp"
#include "MyShot.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

class MaxChargeLaser : public MyShot {
    public:
        MaxChargeLaser(MyTexture* t, int xpos, int ypos);
        void move();
        void render(SDL_Renderer** gRenderer);
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
};

#endif /* MaxChargeLaser_hpp */
