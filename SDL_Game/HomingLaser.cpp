//
//  HomingLaser.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-17.
//

// Functions for the HomingLaser class

#include "HomingLaser.hpp"
#include <stdio.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

HomingLaser::HomingLaser(int xpos, int ypos) {
    rectangle.x = xpos;
    rectangle.y = ypos;
    rectangle.w = 10;
    rectangle.h = 10;
    xvel = 0;
    yvel = 0;
    onscreen = true;
    existTimer.start();
}

void HomingLaser::move(SDL_Rect playerRect) {
    int x1 = rectangle.x;
    int y1 = rectangle.y;
    int x2 = playerRect.x + 15;
    int y2 = playerRect.y + 15;
    
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    xvel = dx/50;
    yvel = dy/50;
    
    rectangle.x += xvel;
    if(rectangle.x < 0 || rectangle.x >= 640) {
        onscreen = false;
    }
    rectangle.y += yvel;
    if(rectangle.y < 0 || rectangle.y >= 480) {
        onscreen = false;
    }
    if(existTimer.getTicks() >= 2500) {
        onscreen = false;
    }
}

int HomingLaser::getType() {
    return 1;
}
