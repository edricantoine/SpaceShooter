//
//  Player.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-20.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"
#include "MyTimer.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Class for the player ship

class Player {
    public:
        static const int VEL = 5;
    // constructor
        Player();
    // handles directional input
        void handleEvent(SDL_Event& e);
    // moves based on velX and velY
        void move();
    // makes the ship disappear and sets alive to false
        void kill(MyTexture* spaceTexture, SDL_Renderer** gRenderer);
    // renders w/ appropriate texture
        void render(MyTexture* playerTexture, SDL_Renderer ** gRenderer, double angle);
    // resets coordinates + dimensions
        void reset();
    // getters & setters
        SDL_Rect getRect();
        bool getAlive();
        bool getHit();
        int getHp();
    // INCREASES hp by i
        void incHp(int i);
        int getMode();
        void setMode(int i);
    // what to do on hit
        void onHit();
    
    
    
    private:
    // rectangle representing this ship
        SDL_Rect rectangle;
    // velocity
        int velX;
        int velY;
    // is it alive
        bool isAlive;
    // is it hit
        bool isHit;
    // no. of hits this player can take before dying
        int hp;
    // timer for flashing red after hit
        MyTimer hitTimer;
    
        // Powerup mode: 0 = normal, 1 = shield, 2 = spread, 3 = piercing, 4 = charge
        int mode;
        
};

#endif /* Player_hpp */
