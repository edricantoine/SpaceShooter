//
//  SpreadShooter.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-18.
//

// Class for the SpreadShooter enemy

#ifndef SpreadShooter_hpp
#define SpreadShooter_hpp

#include <stdio.h>
#include "BadGuy.h"
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

class SpreadShooter: public BadGuy {
public:
    SpreadShooter();
    void move(SDL_Rect playerRect);
    void shoot(SDL_Rect playerRect, vector<Shot*>& badShots);
    void render(MyTexture* enemyTexture, SDL_Renderer** gRenderer, double angle);
    void setVelX();
    void setVelY();
    void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
    void setStartingXpos();
    void setStartingYpos();
    int getType();
    int getHp();
private:
    MyTimer shootTimer;
    MyTimer moveTimer;
    int hp;
};

#endif /* SpreadShooter_hpp */
