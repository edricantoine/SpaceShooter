//
//  Player.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-20.
//

#include "Player.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"

// Functions for Player class

Player::Player() {
    rectangle.x = 50;
    rectangle.y = SCREEN_HEIGHT / 2;
    rectangle.w = 30;
    rectangle.h = 30;
    velX = 0;
    velY = 0;
    isAlive = true;
    isHit = false;
    hp = 3;
    mode = 0; //initiaize to "normal" powerup mode (no powerups)
}

void Player::reset() {
    rectangle.x = 50;
    rectangle.y = SCREEN_HEIGHT / 2;
    rectangle.w = 30;
    rectangle.h = 30;
    velX = 0;
    velY = 0;
    hp = 3;
    isAlive = true;
}

void Player::handleEvent(SDL_Event& e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w:
                velY -= VEL;
                break;
            case SDLK_a:
                velX -= VEL;
                break;
            case SDLK_s:
                velY += VEL;
                break;
            case SDLK_d:
                velX += VEL;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_w:
                velY += VEL;
                break;
            case SDLK_a:
                velX += VEL;
                break;
            case SDLK_s:
                velY -= VEL;
                break;
            case SDLK_d:
                velX -= VEL;
                break;
        }
    }
}

void Player::move() {
    // movement w/ bounds detection
    rectangle.x += velX;
    if((rectangle.x < 0) || (rectangle.x + rectangle.w > SCREEN_WIDTH)) {
        rectangle.x -= velX;
    }
    rectangle.y += velY;
    if((rectangle.y < 0) || (rectangle.y + rectangle.h > (SCREEN_HEIGHT - (SCREEN_HEIGHT / 5)))) {
        rectangle.y -= velY;
    }
    if(hitTimer.isStarted() && hitTimer.getTicks() >= 1500) {
        isHit = false;
        hitTimer.stop();
    }
}

void Player::kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer) {
    if(mode != 1) {
        hp--;
    }
    if(hp <= 0) {
        (*spaceTexture).render(rectangle.x, rectangle.y, gRenderer);
        isAlive = false;
    }
}

void Player::render(MyTexture* playerTexture, SDL_Renderer ** gRenderer, double angle) {
    (*playerTexture).render(rectangle.x, rectangle.y, gRenderer, angle);
}

SDL_Rect Player::getRect() {
    return rectangle;
}

bool Player::getAlive() {
    return isAlive;
}

int Player::getHp() {
    return hp;
}

void Player::incHp(int i) {
    hp += i;
    if(hp > 3) {
        hp = 3;
    }
}

void Player::onHit() {
    isHit = true;
    hitTimer.start();
    mode = 0;
}

bool Player::getHit() {
    return isHit;
}

int Player::getMode() {
    return mode;
}

void Player::setMode(int i) {
    mode = i;
}
