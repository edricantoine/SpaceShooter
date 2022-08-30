//
//  funcs.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-07.
//
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};



SDL_Texture* loadTexturePNG(std::string path, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    //attempts to load surface and apply to texture
    if(loadedSurface == NULL) {
        printf("Could not load the image: %s.\n", SDL_GetError());
        return NULL;
    } else {
        newTexture = SDL_CreateTextureFromSurface(*gRenderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Could not create Texture: %s.\n", SDL_GetError());
            return NULL;
        }
        SDL_FreeSurface(loadedSurface);
        return newTexture;
    }
}

//initializes SDL processes + window + main surface
bool init(SDL_Window** gWindow, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer) {
    bool success = true;
    //attempts to initialize video and audio
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Could not initialize SDL2: %s. \n", SDL_GetError());
        success = false;
    } else {
        // attempts to create window
        *gWindow = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(*gWindow == NULL) {
            printf("Window error: %s. \n", SDL_GetError());
            success = false;
        } else {
            //attempts to create renderer
            *gRenderer = SDL_CreateRenderer(*gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(*gRenderer == NULL) {
                printf("Renderer could not be created.\n");
                success = false;
            } else {
                // attempts to set renderer color
                SDL_SetRenderDrawColor(*gRenderer, 0xff, 0xff, 0xff, 0xff);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_Image could not initialize.\n");
                    success = false;
                } else {
                    *gScreenSurface = SDL_GetWindowSurface(*gWindow);
                }
                
                // attempts to initialize TTF plugin
                if(TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize.\n");
                    success = false;
                }
                
                // attempts to initialize audio plugin
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("Could not initialize music.\n");
                    success = false;
                }

            }
        } 
        
    }
    return success;
}

bool loadMedia(SDL_Surface** gKeyPressSurfaces, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, SDL_Texture** gTexture, SDL_Texture** spaceTexture) {
    bool success = true;
    // attempts to load texture
    *gTexture = loadTexturePNG("SDL_Game/bluesquaresmall.png", gScreenSurface, gRenderer);
    if(*gTexture == NULL) {
        printf("Could not load ship texture.\n");
        success = false;
    }
    // attempts to load space texture
    *spaceTexture = loadTexturePNG("SDL_Game/space.png", gScreenSurface, gRenderer);
    if(*spaceTexture == NULL) {
        printf("Could not load space texture.\n");
        success = false;
    }     
   
    return success;
}


void refreshCycle(SDL_Renderer** gRenderer, SDL_Rect topViewport, SDL_Rect bottomViewport, double* angle, MyTexture* spaceTexture, MyTexture* textTexture, MyTexture* timerTexture, MyTexture* scoreTexture) {
    SDL_SetRenderDrawColor(*gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(*gRenderer);
    // render space texture and text texture to top viewport
    SDL_RenderSetViewport(*gRenderer, &topViewport);
    (*spaceTexture).render(0, 0, gRenderer);
    (*timerTexture).render(0, 0, gRenderer);
    (*scoreTexture).render(0, (*timerTexture).getHeight(), gRenderer);
    // render space texture to bottom viewport
    SDL_RenderSetViewport(*gRenderer, &bottomViewport);
    (*spaceTexture).render(0, 0, gRenderer);
    // draw line on top viewport
    SDL_RenderSetViewport(*gRenderer, &topViewport);
    SDL_SetRenderDrawColor(*gRenderer, 0x00, 0xff, 0x00, 0xff);

    SDL_RenderDrawLine(*gRenderer, 0, (SCREEN_HEIGHT / 5) - 1, SCREEN_WIDTH, (SCREEN_HEIGHT / 5) - 1);
    
    SDL_RenderSetViewport(*gRenderer, &bottomViewport);
    // increment and handle angle
    (*angle)++;
    if(*angle >= 360.0) {
        *angle = 0.0;
    }
}

void refreshCyclePregame(SDL_Renderer** gRenderer, SDL_Rect topViewport, SDL_Rect bottomViewport, MyTexture* spaceTexture, MyTexture* startTexture) {
    // clears bottom viewport
    SDL_SetRenderDrawColor(*gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(*gRenderer);
    // renders space texture and start text to top viewport
    SDL_RenderSetViewport(*gRenderer, &topViewport);
    (*spaceTexture).render(0, 0, gRenderer);
    (*startTexture).render(0,0,gRenderer);
    // renders space texture to bottom viewport
    SDL_RenderSetViewport(*gRenderer, &bottomViewport);
    (*spaceTexture).render(0, 0, gRenderer);
    SDL_RenderSetViewport(*gRenderer, &topViewport);
    // draws line separating two viewports
    SDL_SetRenderDrawColor(*gRenderer, 0x00, 0xff, 0x00, 0xff);

    SDL_RenderDrawLine(*gRenderer, 0, (SCREEN_HEIGHT / 5) - 1, SCREEN_WIDTH, (SCREEN_HEIGHT / 5) - 1);
    
    SDL_RenderSetViewport(*gRenderer, &bottomViewport);
    
}

//closes SDL window and quits everything
void close(SDL_Window** gWindow, SDL_Surface** gTestImg, SDL_Renderer** gRenderer, Mix_Music** music) {
    //destroy music
    Mix_FreeMusic(*music);
    //destroy test image
    SDL_FreeSurface(*gTestImg);
    *gTestImg = NULL;
    //destroy window
    SDL_DestroyRenderer(*gRenderer);
    SDL_DestroyWindow(*gWindow);
    *gWindow = NULL;
    *gRenderer = NULL;
    //quit subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
}
    
    
