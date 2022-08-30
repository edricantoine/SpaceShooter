//
//  MyShot.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-28.
//

#include "MyShot.hpp"
#include "MyTexture.hpp"
#include "Enemy.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

MyShot::MyShot(MyTexture* t) {
    texture = t;
}

MyShot::~MyShot() {
    
}

void MyShot::render(SDL_Renderer** gRenderer) {
    (*texture).render(rectangle.x, rectangle.y, gRenderer);
}

void MyShot::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    onscreen = false;
    (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
}

int MyShot::getXvel() {
    return xvel;
}

int MyShot::getYvel() {
    return yvel;
}

SDL_Rect MyShot::getRect() {
    return rectangle;
}

bool MyShot::getOnscreen() {
    return onscreen;
}



