//
//  Shot.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-26.
//

// Functions for "Shot" class

#include "Shot.hpp"
#include "MyTexture.hpp"
#include "MyTimer.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

Shot::~Shot() {
    
}

int Shot::getXvel() {
    return xvel;
}

int Shot::getYvel() {
    return yvel;
}

bool Shot::getOnscreen() {
    return onscreen;
}

SDL_Rect Shot::getRect() {
    return rectangle;
}

void Shot::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    onscreen = false;
    (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
}

void Shot::render(MyTexture* texture, SDL_Renderer** gRenderer) {
    (*texture).render(rectangle.x, rectangle.y, gRenderer);
}
