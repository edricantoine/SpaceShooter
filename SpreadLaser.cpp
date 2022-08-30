//
//  SpreadLaser.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-29.
//

#include "SpreadLaser.hpp"
#include "MyTexture.hpp"
#include "Enemy.hpp"
#include "MyShot.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

SpreadLaser::SpreadLaser(MyTexture* t, int xpos, int ypos, int Xvel, int Yvel) : MyShot(t) {
    rectangle.x = xpos;
    rectangle.y = ypos;
    rectangle.w = 10;
    rectangle.h = 10;
    xvel = Xvel;
    yvel = Yvel;
    onscreen = true;
}

void SpreadLaser::move() {
    rectangle.x += xvel;
    rectangle.y += yvel;
    if(rectangle.x >= 640 || rectangle.y >= 480 || rectangle.y <= 0) {
        onscreen = false;
    }
}
