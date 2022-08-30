//
//  Wave.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-24.
//

#include "Wave.hpp"
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
#include "StraightShooter.hpp"
#include "BadGuy.h"
#include "HomingTurret.hpp"
#include "SpreadShooter.hpp"
#include "Orbiter.hpp"

using namespace std;

// 20 possible waves, they loop after all 20 are completed

Wave::Wave(int waveNum) {
    switch(waveNum) {
        case 1: {
            vector<BadGuy*> v;
            for(int i = 0; i < 1; i++) {
                v.push_back(new Enemy());
            }
            baddies.push_back(v);
            break;
        }
        case 2: {
            vector<BadGuy*> v;
            for(int i = 0; i < 8; i++) {
                v.push_back(new Enemy());
            }
            baddies.push_back(v);
            
            vector<BadGuy*> v2;
            for(int i = 0; i < 3; i++) {
                v2.push_back(new StraightShooter());
            }
            baddies.push_back(v2);
            break;
        }
        case 3: {
            vector<BadGuy*> v;
            for(int i = 0; i < 3; i++) {
                v.push_back(new Enemy());
            }
            for(int i = 0; i < 3; i++) {
                v.push_back(new StraightShooter());
            }
            baddies.push_back(v);
            
            vector<BadGuy*> v2;
            for(int i = 0; i < 3; i++) {
                v2.push_back(new StraightShooter());
            }
            for(int i = 0; i < 5; i++) {
                v2.push_back(new Enemy());
            }
            baddies.push_back(v2);
            break;
        }
        case 4: {
            vector<BadGuy*> v;
            for(int i = 0; i < 3; i++) {
                v.push_back(new Enemy());
            }
            for(int i = 0; i < 3; i++) {
                v.push_back(new StraightShooter());
            }
            baddies.push_back(v);
            
            vector<BadGuy*> v2;
            for(int i = 0; i < 2; i++) {
                v2.push_back(new StraightShooter());
            }
            for(int i = 0; i < 5; i++) {
                v2.push_back(new Enemy());
            }
            baddies.push_back(v2);
            
            vector<BadGuy*> v3;
            for(int i = 0; i < 7; i++) {
                v3.push_back(new Enemy());
            }
            baddies.push_back(v3);
            break;
        }
        case 5: {
            vector<BadGuy*> v;
            for(int i = 0; i < 8; i++) {
                v.push_back(new Enemy());
            }
            baddies.push_back(v);
            
            vector<BadGuy*> v2;
            for(int i = 0; i < 3; i++) {
                v2.push_back(new Enemy());
            }
            for(int i = 0; i < 3; i++) {
                v2.push_back(new HomingTurret());
            }
            baddies.push_back(v2);
            break;
        }
        case 6: {
            break;
        }
        case 7: {
            break;
        }
        case 8: {
            break;
        }
        case 9: {
            break;
        }
        case 10: {
            break;
        }
        case 11: {
            break;
        }
        case 12: {
            break;
        }
        case 13: {
            break;
        }
        case 14: {
            break;
        }
        case 15: {
            break;
        }
        case 16: {
            break;
        }
        case 17: {
            break;
        }
        case 18: {
            break;
        }
        case 19: {
            break;
        }
        case 20: {
            break;
        }
            
    }
    if(waveNum == 20) {
        isBossWave = true;
    } else {
        isBossWave = false;
    }
}

vector<vector<BadGuy*>> Wave::getBaddies() {
    return baddies;
}

// clear vector and delete allocated memory

void Wave::endWave() {
    for(int i = 0; i < baddies.size(); i++) {
        for(int j = 0; j < baddies[i].size(); j++) {
            delete baddies[i][j];
        }
        baddies[i].clear();
    }
    baddies.clear();
}

bool Wave::getIsBossWave() {
    return isBossWave;
}
