//
//  HomingTurret.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-18.
//

// Functions for homing missile turret class

#include "HomingTurret.hpp"
#include "MyTexture.hpp"
#include "HomingLaser.hpp"
#include "BadLaser.hpp"
#include "MyTimer.hpp"
#include "Shot.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

HomingTurret::HomingTurret() {
    rectangle.w = 30;
    rectangle.h = 30;
    rectangle.x = 600;
    rectangle.y = 0;
    
    hp = 3;
    
    velX = 0;
    velY = 0;
    
    isDead = false;
    isHit = false;
    spawned = false;
    isInit = false;
    
    setStartingYpos();
    setStartingXpos();
    
    shootTimer.start();
}

void HomingTurret::move(SDL_Rect playerRect) {
    if(!isInit) {
        spawnTimer.start();
        isInit = true;
    }
    if(hitTimer.isStarted() && hitTimer.getTicks() >= 100) {
        isHit = false;
        hitTimer.stop();
    }
}

void HomingTurret::render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle) {
    if(spawned == true) {
        (*enemyTexture).render(rectangle.x, rectangle.y, gRenderer, angle);
    } else {
        (*enemyTexture).render(rectangle.x, rectangle.y, gRenderer, 0.0);
    }
}


void HomingTurret::setStartingXpos() {
    int xpos = (rand() % 600);
    rectangle.x = xpos;
}

void HomingTurret::setStartingYpos() {
    int ypos = (rand() % (450 - (450 / 5)));
    rectangle.y = ypos;
}

void HomingTurret::shoot(SDL_Rect playerRect, vector<Shot*>& badShots) {
    if(spawnTimer.getTicks() >= 2000) {
        spawned = true;
        if(shootTimer.getTicks() >= 2000) {
            shootTimer.start();
            badShots.push_back(new HomingLaser(rectangle.x + 15, rectangle.y + 15));
        }
    }
}

void HomingTurret::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    hp--;
    if(hp == 0) {
        (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
        isDead = true;
    }
}

void HomingTurret::setVelX() {
    return;
}

void HomingTurret::setVelY() {
    return;
}

int HomingTurret::getType() {
    return 2;
}

int HomingTurret::getHp() {
    return hp;
}

bool HomingTurret::getSpawned() {
    return spawned;
}

MyTimer HomingTurret::getShootTimer() {
    return shootTimer;
}

MyTimer HomingTurret::getSpawnTimer() {
    return spawnTimer;
}
