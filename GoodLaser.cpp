//
//  GoodLaser.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-22.
//

#include "GoodLaser.hpp"
#include "MyTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

// functions for GoodLaser class

GoodLaser::GoodLaser(MyTexture* t, int xpos, int ypos) : MyShot(t) {
    rectangle.x = xpos;
    rectangle.y = ypos;
    rectangle.w = 10;
    rectangle.h = 5;
    xvel = 7;
    yvel = 0;
    onscreen = true;
}

void GoodLaser::move() {
    rectangle.x += xvel;
    if(rectangle.x >= 640) {
        onscreen = false;
    }
}

