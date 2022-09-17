//
//  MaxChargeLaser.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-09-03.
//

#include "MaxChargeLaser.hpp"
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

MaxChargeLaser::MaxChargeLaser(MyTexture* t, int xpos, int ypos) : MyShot(t) {
    rectangle.x = xpos;
    rectangle.y = ypos;
    rectangle.w = 40;
    rectangle.h = 40;
    xvel = 7;
    yvel = 0;
    onscreen = true;
}

void MaxChargeLaser::move() {
    rectangle.x += xvel;
    if(rectangle.x >= 640) {
        onscreen = false;
    }
}

void MaxChargeLaser::render(SDL_Renderer** gRenderer) {
    Uint64 ticks = SDL_GetTicks64();
    int sprite = (ticks / 100) % 2;
    if(sprite == 0) {
        (*texture).renderPart(rectangle.x, rectangle.y, gRenderer, 0, 0, 40, 40);
    } else {
        (*texture).renderPart(rectangle.x, rectangle.y, gRenderer, 0, 40, 40, 40);
    }
}

void MaxChargeLaser::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    return;
}
