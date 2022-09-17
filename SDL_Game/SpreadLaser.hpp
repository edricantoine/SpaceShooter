//
//  SpreadLaser.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-29.
//

// Class for the laser that you shoot as a spread shot.

#ifndef SpreadLaser_hpp
#define SpreadLaser_hpp

#include <stdio.h>
#include "MyTexture.hpp"
#include "Enemy.hpp"
#include "MyShot.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

class SpreadLaser : public MyShot {
    public:
        SpreadLaser(MyTexture* t, int xpos, int ypos, int xvel, int yvel);
        void move();
};

#endif /* SpreadLaser_hpp */
