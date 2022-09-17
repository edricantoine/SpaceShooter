//
//  SpreadPow.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-27.
//

#include "SpreadPow.hpp"
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

SpreadPow::SpreadPow(MyTexture* t, int xpos, int ypos) : PowerUp(t, xpos, ypos) {
    return;
}

void SpreadPow::takeEffect(Player& p) {
    p.setMode(2);
    isActive = false;
}
