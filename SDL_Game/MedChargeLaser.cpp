//
//  MedChargeLaser.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-30.
//

#include "MedChargeLaser.hpp"
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

MedChargeLaser::MedChargeLaser(MyTexture* t, int xpos, int ypos) : MyShot(t) {
    rectangle.x = xpos;
    rectangle.y = ypos;
    rectangle.w = 30;
    rectangle.h = 10;
    xvel = 7;
    yvel = 0;
    onscreen = true;
}

void MedChargeLaser::move() {
    rectangle.x += xvel;
    if(rectangle.x >= 640) {
        onscreen = false;
    }
}
