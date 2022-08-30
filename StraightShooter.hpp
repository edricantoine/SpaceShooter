//
//  StraightShooter.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-10.
//

#ifndef StraightShooter_hpp
#define StraightShooter_hpp
#include "BadGuy.h"
#include "BadLaser.hpp"
#include "HomingLaser.hpp"
#include "Shot.hpp"
#include <vector>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"

#include <stdio.h>

using namespace std;

// Enemy that shoots straight and moves in a line

class StraightShooter: public BadGuy {
    public:
    // see "BadGuy" class
        StraightShooter();
        void move(SDL_Rect playerRect);
        void shoot(SDL_Rect playerRect, vector<Shot*>& badShots);
        void render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle);
        void setVelX();
        void setVelY();
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
    // both starting Y position and X position need to be set
        void setStartingYpos();
        void setStartingXpos();
        int getType();
    
    private:
    // timer dictating how frequently this guy can shoot and change direction
        MyTimer shootTimer;
        MyTimer moveTimer;
};

#endif /* StraightShooter_hpp */
