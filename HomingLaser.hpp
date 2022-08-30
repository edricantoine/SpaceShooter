//
//  HomingLaser.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-08-17.
//

//Class for homing bullets

#ifndef HomingLaser_hpp
#define HomingLaser_hpp

#include <stdio.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"
#include "Shot.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cstdlib>
#include <ctime>

class HomingLaser: public Shot{
    public:
        HomingLaser(int xpos, int ypos);
        void move(SDL_Rect playerRect);
        void render(MyTexture* texture, SDL_Renderer** gRenderer);
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
        int getXVel();
        int getYVel();
        bool getOnscreen();
        SDL_Rect getRect();
        int getType();
    private:
        MyTimer existTimer;
        
};

#endif /* HomingLaser_hpp */
