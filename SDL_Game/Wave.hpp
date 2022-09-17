//
//  Wave.hpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-24.
//

#ifndef Wave_hpp
#define Wave_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Enemy.hpp"
#include "BadGuy.h"

using namespace std;

// Class representing a Wave in the game

class Wave {
    
    public:
    // wave layout is different depending on wave num
        Wave(int waveNum);
    // all bad guys in all sub waves of this wave
        vector<vector<BadGuy*>> getBaddies();
    // frees memory, clears vectors, cures cancer
        void endWave();
    //getter
        bool getIsBossWave();
        
    private:
        vector<vector<BadGuy*>> baddies;
        bool isBossWave;
};

#endif /* Wave_hpp */
