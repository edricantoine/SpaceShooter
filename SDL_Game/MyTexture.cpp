//
//  MyTexture.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-09.
//

#include "MyTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

// functions for MyTexture class

MyTexture::MyTexture() {
    mTexture = NULL;
    width = 0;
    height = 0;
}

MyTexture::~MyTexture() {
    free();
}


bool MyTexture::loadFromFile(std::string path, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, bool colorKey) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    //attempt to load surface from image
    if(loadedSurface == NULL) {
        printf("Could not load the image: %s.\n", SDL_GetError());
        return NULL;
    } else {
        if(colorKey) {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        }
        // attempt to create texture from surface
        newTexture = SDL_CreateTextureFromSurface(*gRenderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Could not create Texture: %s.\n", SDL_GetError());
            return NULL;
        } else {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool MyTexture::loadFromText(std::string textString, SDL_Renderer** gRenderer, SDL_Color textColor, TTF_Font** gFont) {
    free();
    // attempt to render text into a surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(*gFont, textString.c_str(), textColor);
    if(textSurface == NULL) {
        printf("Unable to render text.\n");
    } else {
        
        //attempt to create texture from surface
        mTexture = SDL_CreateTextureFromSurface(*gRenderer, textSurface);
        if(mTexture == NULL) {
            printf("Unable to create texture from text surface.\n");
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    
    return mTexture != NULL;
    
}

void MyTexture::render(int x, int y, SDL_Renderer** gRenderer, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopyEx(*gRenderer, mTexture, NULL, &renderQuad, angle, center, flip);
}

void MyTexture::renderPart(int x, int y, SDL_Renderer** gRenderer, int x2, int y2, int w2, int h2, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect srcQuad = {x2, y2, w2, h2};
    SDL_Rect destQuad = {x, y, w2, h2};
    SDL_RenderCopyEx(*gRenderer, mTexture, &srcQuad, &destQuad, angle, center, flip);
}

void MyTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void MyTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void MyTexture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void MyTexture::free(){
    if(mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        width = 0;
        height = 0;
    }
}

int MyTexture::getWidth() {
    return width;
}

int MyTexture::getHeight() {
    return height;
}
