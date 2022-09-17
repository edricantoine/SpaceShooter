//
//  BadLaser.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-10.
//

#include "BadLaser.hpp"
#include "MyTexture.hpp"
#include "Shot.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

BadLaser::BadLaser(int xpos, int ypos, bool forward) {
    rectangle.x = xpos;
    rectangle.y = ypos;
    rectangle.w = 10;
    rectangle.h = 5;
    yvel = 0;
    // forward dictates whether velocity is pos. or neg.
    if(forward) {
        xvel = 5;
    } else {
        xvel = -5;
    }
    onscreen = true;
}

void BadLaser::move(SDL_Rect playerRect) {
    rectangle.x += xvel;
    if(rectangle.x < 0 || rectangle.x >= 640) {
        onscreen = false;
    }
}

int BadLaser::getType() {
    return 0;
}

