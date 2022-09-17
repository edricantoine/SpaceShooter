//
//  BadGuy.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-24.
//
#include "BadGuy.h"
#include "MyTexture.hpp"
#include "Shot.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

// Non-virtual functions for BadGuy abstract class (just getters + destructor)

BadGuy::BadGuy() {
    setWillDropItem();
    setItemToDrop();
}

bool BadGuy::getDead() {
    return isDead;
}

int BadGuy::getVelY() {
    return velY;
}

int BadGuy::getVelX() {
    return velX;
}

SDL_Rect BadGuy::getRect() {
    return rectangle;
}

BadGuy::~BadGuy() {

}

bool BadGuy::getHit() {
    return isHit;
}

void BadGuy::onHit() {
    isHit = true;
    hitTimer.start();
}

void BadGuy::setWillDropItem() {
    int temp = rand() % 8;
    if(temp == 0) {
        willDropItem = true;
    } else {
        willDropItem = false;
    }
}

void BadGuy::setItemToDrop() {
    itemToDrop = (rand() % 5) + 1;
}

bool BadGuy::willDrop() {
    return willDropItem;
}

int BadGuy::itemDrop() {
    return itemToDrop;
}
