//
//  LifePow.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-27.
//

#include "LifePow.hpp"
#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "MyTimer.hpp"
#include "HomingLaser.hpp"
#include "Player.hpp"
#include "PowerUp.hpp""
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <stdio.h>

LifePow::LifePow(MyTexture* t, int xpos, int ypos) : PowerUp(t, xpos, ypos) {
    return;
}

void LifePow::takeEffect(Player& p) {
    p.incHp(1);
    isActive = false;
}
