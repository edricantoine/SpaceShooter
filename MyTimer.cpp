//
//  MyTimer.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-19.
//

#include "MyTimer.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

// functions for MyTimer class

MyTimer::MyTimer() {
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void MyTimer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks64();
    pausedTicks = 0;
}

void MyTimer::stop() {
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void MyTimer::pause() {
    if(started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks64() - startTicks;
        startTicks = 0;
    }
}

void MyTimer::unpause() {
    if(started && paused) {
        paused = false;
        startTicks = SDL_GetTicks64() - pausedTicks;
        pausedTicks = 0;

    }
}

Uint64 MyTimer::getTicks() {
    Uint64 time = 0;
    if(started) {
        if(paused) {
            time = pausedTicks;
        } else {
            time = SDL_GetTicks64() - startTicks;
        }
    }
    return time;
}

bool MyTimer::isStarted() {
    return started;
}

bool MyTimer::isPaused() {
    return started && paused;
}
