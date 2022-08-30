//
//  main.h
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-07.
//

// Header file for funcs file

#ifndef main_h
#define main_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "MyTexture.hpp"


// Initializes window
bool init(SDL_Window** gWindow, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer);
// Loads some media and textures
bool loadMedia(SDL_Surface** gKeyPressSurfaces, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, SDL_Texture** gTexture, SDL_Texture** spaceTexture);
// Closes window, quits processes, frees memory, cures cancer
void close(SDL_Window** gWindow, SDL_Surface** gTestImg, SDL_Renderer** gRenderer, Mix_Music** music);


// Loads a texture string
SDL_Texture* loadTexturePNG(std::string path, SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer);

// Refreshes the screen
void refreshCycle(SDL_Renderer** gRenderer, SDL_Rect topViewport, SDL_Rect bottomViewport, double* angle, MyTexture* spaceTexture, MyTexture* textTexture, MyTexture* timerTexture, MyTexture* scoreTexture);

// Refreshes the screen for pregame
void refreshCyclePregame(SDL_Renderer** gRenderer, SDL_Rect topViewport, SDL_Rect bottomViewport, MyTexture* spaceTexture, MyTexture* startTexture);

#endif /* main_h */
