//
//  StraightShooter.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-10.
//

#include "StraightShooter.hpp"
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

using namespace std;

// Functions for StraightShooter class

StraightShooter::StraightShooter() {
    rectangle.w = 30;
    rectangle.h = 30;
    rectangle.x = 600;
    rectangle.y = 0;
    
    velX = 0;
    velY = 0;
    
    isDead = false;
    isHit = false;
    
    setVelY();
    setVelX();
    
    setStartingYpos();
    setStartingXpos();
    
    shootTimer.start();
    moveTimer.start();
}

// Moves in a straight line, not like asteroids

void StraightShooter::move(SDL_Rect playerRect) {
    if(moveTimer.getTicks() >= 1500) {
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

// can shoot every 1 second, creates a BadLaser (not dynamically, so does not need to be deleted)

void StraightShooter::shoot(SDL_Rect playerRect, vector<Shot*>& badShots) {
    if(shootTimer.getTicks() >= 1000) {
        shootTimer.start();
        if(playerRect.x > rectangle.x) {
            badShots.push_back(new BadLaser(rectangle.x + 10, rectangle.y + 10, true));
        } else {
            badShots.push_back(new BadLaser(rectangle.x + 10, rectangle.y + 10, false));
        }
        
    }
}

void StraightShooter::render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle) {
    (*enemyTexture).render(rectangle.x, rectangle.y, gRenderer, 0.0);
}

void StraightShooter::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    isDead = true;
    (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
}

// starting velocities can be either positive or negative

void StraightShooter::setVelY() {
    int spd = (rand() % 3);
    int n = (rand() % 2);
    if(n == 0) {
        velY = spd;
    } else {
        velY = spd * -1;
    }
}

void StraightShooter::setVelX() {
    int spd = (rand() % 3);
    int n = (rand() % 2);
    if(n == 0) {
        velX = spd;
    } else {
        velX = spd * -1;
    }
}

void StraightShooter::setStartingYpos() {
    int ypos = (rand() % (450 - (450 / 5)));
    rectangle.y = ypos;
}

int StraightShooter::getType() {
    return 1;
}

void StraightShooter::setStartingXpos() {
    rectangle.x = 600;
}
