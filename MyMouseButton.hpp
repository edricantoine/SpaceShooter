//
//  MyMouseButton.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-17.
//

#ifndef MyMouseButton_hpp
#define MyMouseButton_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
class MyMouseButton {
    public:
        MyMouseButton();
        void setPosition(int x, int y);
        void handleEvent(SDL_Event* e);
    
    private:
        SDL_Point position;
};
#endif /* MyMouseButton_hpp */
