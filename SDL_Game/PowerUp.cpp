//
//  PowerUp.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-23.
//

// Functions for Powerup class

#include "PowerUp.hpp"
#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "MyTimer.hpp"
#include "HomingLaser.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <vector>
#include <ctime>

PowerUp::PowerUp(MyTexture* t, int xpos, int ypos) {
    texture = t;
    rectangle.w = 30;
    rectangle.h = 30;
    rectangle.x = xpos;
    rectangle.y = ypos;
    setVelX();
    setVelY();
    isActive = true;
    activeTimer.start();
}

PowerUp::~PowerUp() {
    
}

void PowerUp::move() {
    // enemy bounces off of walls
    rectangle.x += velX;
    if(rectangle.x < 0 || rectangle.x + rectangle.w > 640) {
        rectangle.x -= velX;
        velX = velX * -1;
    }
    rectangle.y += velY;
    if(rectangle.y < 0 || rectangle.y + rectangle.h > (480 - (480/5))) {
        rectangle.y -= velY;
        velY = velY * -1;
    }
    
    if(activeTimer.getTicks() >= 10000) {
        isActive = false;
    }
}

void PowerUp::render(SDL_Renderer** gRenderer) {
    (*texture).render(rectangle.x, rectangle.y, gRenderer);
}

int PowerUp::getVelX() {
    return velX;
}

int PowerUp::getVelY() {
    return velY;
}

SDL_Rect PowerUp::getRect() {
    return rectangle;
}

MyTimer PowerUp::getTimer() {
    return activeTimer;
}

bool PowerUp::getActive() {
    return isActive;
}

MyTexture* PowerUp::getTexture() {
    return texture;
}

void PowerUp::setVelX() {
    int spd = (rand() % 3) + 1;
    velX = spd * -1;
}

void PowerUp::setVelY() {
    int spd = (rand() % 3) + 1;
    velY = spd;
}
