//
//  MyMouseButton.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-17.
//

#include "MyMouseButton.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;

MyMouseButton::MyMouseButton() {
    position.x = 0;
    position.y = 0;
}

void MyMouseButton::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void MyMouseButton::handleEvent(SDL_Event* e) {
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < position.x) {
            inside = false;
        } else if (x > position.x + BUTTON_WIDTH) {
            inside = false;
        } else if (y < position.y) {
            inside = false;
        } else if (y > position.y + BUTTON_HEIGHT) {
            inside = false;
        }
        
        if(!inside) {
        } else {
            switch(e->type) {
                case SDL_MOUSEBUTTONDOWN:
                    printf("Mouse down.\n");
                    break;
                case SDL_MOUSEBUTTONUP:
                    printf("Mouse up.\n");
                    break;
            }
        }
    }
    
    
}
