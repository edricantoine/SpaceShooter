//
//  GoodLaser.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-22.
//

#ifndef GoodLaser_hpp
#define GoodLaser_hpp

#include "MyTexture.hpp"
#include "Enemy.hpp"
#include "MyShot.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

// A class for the lasers the player can shoot

class GoodLaser : public MyShot {
    public:
    // init. with x position and y position
        GoodLaser(MyTexture* t, int xpos, int ypos);
    // move according to velocity
        void move();
  
};

#endif /* GoodLaser_hpp */
