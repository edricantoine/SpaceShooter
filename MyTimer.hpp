//
//  MyTimer.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-19.
//

#ifndef MyTimer_hpp
#define MyTimer_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

// class representing a timer

class MyTimer {
    public:
    // constructor
        MyTimer();
    // starts the timer
        void start();
    // stops
        void stop();
    // pauses
        void pause();
    // I think you get it by now
        void unpause();
    // gets the total ticks so far
        Uint64 getTicks();
    // getters for started and paused
        bool isStarted();
        bool isPaused();
    
    private:
    // ticks when timer was last started
        Uint64 startTicks;
    // ticks when timer was last paused
        Uint64 pausedTicks;
        bool paused;
        bool started;
};

#endif /* MyTimer_hpp */
