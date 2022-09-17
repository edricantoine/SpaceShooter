//
//  ChargePow.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-27.
//

// Charge powerup class

#ifndef ChargePow_hpp
#define ChargePow_hpp

#include <stdio.h>
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

class ChargePow: public PowerUp {
    public:
        ChargePow(MyTexture* t, int xpos, int ypos);
        void takeEffect(Player& p);
};

#endif /* ChargePow_hpp */
