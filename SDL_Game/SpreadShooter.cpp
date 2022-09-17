//
//  SpreadShooter.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-18.
//

#include "SpreadShooter.hpp"
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

SpreadShooter::SpreadShooter() {
    rectangle.x = 600;
    rectangle.y = 0;
    rectangle.w = 30;
    rectangle.h = 90;
    
    hp = 5;
    
    velX = 0;
    velY = 0;
    
    isDead = false;
    isHit = false;
    
    setVelX();
    setVelY();
    
    setStartingXpos();
    setStartingYpos();
    
    shootTimer.start();
    moveTimer.start();
}

void SpreadShooter::move(SDL_Rect playerRect) {
    if(moveTimer.getTicks() >= 2500) {
        moveTimer.start();
        setVelX();
        setVelY();
    }
    rectangle.y += velY;
    
    if(rectangle.y < 0 || rectangle.y + rectangle.h > (480 - (480/5))) {
        rectangle.y -= velY;
        velY = velY * -1;
    }
    
    rectangle.x += velX;
    rectangle.x += velX;
    if(rectangle.x < 0 || rectangle.x + rectangle.w > 640) {
        rectangle.x -= velX;
        velX = velX * -1;
    }
    
    if(hitTimer.isStarted() && hitTimer.getTicks() >= 100) {
        isHit = false;
        hitTimer.stop();
    }
}

void SpreadShooter::shoot(SDL_Rect playerRect, vector<Shot*>& badShots) {
    if(shootTimer.getTicks() >= 2000) {
        shootTimer.start();
        if(playerRect.x <= rectangle.x) {
            badShots.push_back(new BadLaser(rectangle.x + 15, rectangle.y + 45, false));
            badShots.push_back(new BadLaser(rectangle.x + 15, rectangle.y, false));
            badShots.push_back(new BadLaser(rectangle.x + 15, rectangle.y + 80, false));
        }
    }
}

void SpreadShooter::render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle) {
    (*enemyTexture).render(rectangle.x, rectangle.y, gRenderer, 0.0);
}


void SpreadShooter::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    hp--;
    if(hp == 0) {
        (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
        isDead = true;
    }
}

void SpreadShooter::setVelY() {
    int spd = (rand() % 2);
    int n = (rand() % 2);
    if(n == 0) {
        velY = spd;
    } else {
        velY = spd * -1;
    }
}


void SpreadShooter::setVelX() {
    int spd = (rand() % 2);
    int n = (rand() % 2);
    if(n == 0) {
        velX = spd;
    } else {
        velX = spd * -1;
    }
}

int SpreadShooter::getType() {
    return 3;
}

int SpreadShooter::getHp() {
    return hp;
}

void SpreadShooter::setStartingXpos() {
    rectangle.x = 600;
}

void SpreadShooter::setStartingYpos() {
    int ypos = (rand() % (450 - (450 / 5)));
    rectangle.y = ypos;
}


