//
//  MyTexture.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-09.
//

#ifndef MyTexture_hpp
#define MyTexture_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

// Class representing a texture

class MyTexture {
    public:
    // constructor
        MyTexture();
    // destructor
        ~MyTexture();
    //loads texture from file string
        bool loadFromFile(std::string path, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, bool colorKey);
    // loads texture straight from text
        bool loadFromText(std::string textString, SDL_Renderer** gRenderer, SDL_Color textColor, TTF_Font** gFont);
    // frees this texture
        void free();
    // sets texture hue
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
    // sets blend mode
        void setBlendMode(SDL_BlendMode blending);
    // sets alpha
        void setAlpha(Uint8 alpha);
    // renders at (x, y), with gRenderer, at angle, with center and flip
        void render(int x, int y, SDL_Renderer** gRenderer, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // like above, but renders a part of a texture with params x2 y2 w2 and h2
        void renderPart(int x, int y, SDL_Renderer** gRenderer, int x2, int y2, int w2, int h2, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // getters for texture width + height
        int getWidth();
        int getHeight();
        
    private:
    // the actual SDL_Texture
        SDL_Texture* mTexture;
    // width and height
        int width;
        int height;
    
};

#endif /* MyTexture_hpp */
