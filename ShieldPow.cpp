//
//  ShieldPow.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-27.
//

// Functions for shield powerup

#include "ShieldPow.hpp"
#include "MyTexture.hpp"
#include "BadLaser.hpp"
#include "MyTimer.hpp"
#include "HomingLaser.hpp"
#include "Player.hpp"
#include "PowerUp.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <stdio.h>

ShieldPow::ShieldPow(MyTexture* t, int xpos, int ypos) : PowerUp(t, xpos, ypos) {
    return;
}

void ShieldPow::takeEffect(Player& p) {
    p.setMode(1);
    isActive = false;
}
