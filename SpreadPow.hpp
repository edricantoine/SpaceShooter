//
//  SpreadPow.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-27.
//
// Spreadshot powerup class

#ifndef SpreadPow_hpp
#define SpreadPow_hpp

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

class SpreadPow: public PowerUp {
    public:
        SpreadPow(MyTexture* t, int xpos, int ypos);
        void takeEffect(Player& p);
};

#endif /* SpreadPow_hpp */
