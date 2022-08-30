//
//  Orbiter.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-19.
//

// Functions for "Orbiter" enemy

const int RADIUS = 50;

#include "Orbiter.hpp"
#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "HomingLaser.hpp"
#include "MyTimer.hpp"
#include "Shot.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <stdio.h>

Orbiter::Orbiter() {
    rectangle.w = 30;
    rectangle.h = 30;
    rectangle.x = 0;
    rectangle.y = 0;
    hp = 3;
    isInit = false;
    velX = 0;
    velY = 0;
    angle = 0;
    isDead = false;
    isHit = false;
    shootTimer.start();
}

void Orbiter::setVelX() {
    return;
}

void Orbiter::setVelY() {
    return;
}

void Orbiter::setStartingPos(SDL_Rect playerRect) {
    int centerX = playerRect.x + 15;
    int centerY = playerRect.y + 15;
    double angleInRadians = (angle * M_PI) / 180.0;
    rectangle.x = centerX + (cos(angleInRadians) * RADIUS) - 15;
    rectangle.y = centerY + (sin(angleInRadians) * RADIUS) - 15;
}

void Orbiter::move(SDL_Rect playerRect) {
    setStartingPos(playerRect);
    angle += 3;
    if(angle >= 360) {
        angle = 0;
    }
    if(hitTimer.isStarted() && hitTimer.getTicks() >= 100) {
        isHit = false;
        hitTimer.stop();
    }
}

void Orbiter::shoot(SDL_Rect playerRect, vector<Shot*>& badShots) {
    if(shootTimer.getTicks() >= 3000) {
        shootTimer.start();
        badShots.push_back(new HomingLaser(rectangle.x + 15, rectangle.y + 15));
    }
}

void Orbiter::render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle) {
    (*enemyTexture).render(rectangle.x, rectangle.y, gRenderer, angle);
}

void Orbiter::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    hp--;
    if(hp == 0) {
        (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
        isDead = true;
    }
}

int Orbiter::getType() {
    return 4;
}

int Orbiter::getHp() {
    return hp;
}
