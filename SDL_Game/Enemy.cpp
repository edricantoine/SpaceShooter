//
//  Enemy.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-20.
//

#include "Enemy.hpp"
#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "HomingLaser.hpp"
#include "Shot.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// Functions for the Enemy (asteroid) class

Enemy::Enemy() {
    rectangle.w = 30;
    rectangle.h = 30;
    rectangle.x = 600;
    rectangle.y = 0;
    velX = 0;
    velY = 0;
    isDead = false;
    isHit = false;
    setVelX();
    setVelY();
    setStartingYpos();
}
// this is why we need the random seed thing
void Enemy::setVelX() {
    int spd = (rand() % 3) + 1;
    velX = spd * -1;
}

void Enemy::setVelY() {
    int spd = (rand() % 3) + 1;
    velY = spd;
}

void Enemy::setStartingYpos() {
    int ypos = (rand() % (450 - (450 / 5)));
    rectangle.y = ypos;
//    printf("%i\n", ypos);
}

void Enemy::shoot(SDL_Rect playerRect, vector<Shot*>& badShots) {
    return;
}


void Enemy::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    isDead = true;
    (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
}


void Enemy::move(SDL_Rect playerRect) {
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
    
    if(hitTimer.isStarted() && hitTimer.getTicks() >= 100) {
        isHit = false;
        hitTimer.stop();
    }
}

int Enemy::getType() {
    return 0;
}

void Enemy::render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle) {
    (*enemyTexture).render(rectangle.x, rectangle.y, gRenderer, angle);
}

