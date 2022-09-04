//
//  main.cpp
//  SDL_Game
//
//  Created by Edric Antoine on 2022-07-07.
//

//importing SDL and standard IO

//The main file, where the game loop and some helper functions are

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "MyTexture.hpp"
#include "MyMouseButton.hpp"
#include "MyTimer.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "StraightShooter.hpp"
#include "HomingTurret.hpp"
#include "SpreadShooter.hpp"
#include "BadGuy.h"
#include "GoodLaser.hpp"
#include "SpreadLaser.hpp"
#include "BadLaser.hpp"
#include "HomingLaser.hpp"
#include "Wave.hpp"
#include "PowerUp.hpp"
#include "ShieldPow.hpp"
#include "SpreadPow.hpp"
#include "LifePow.hpp"
#include "PiercePow.hpp"
#include "ChargePow.hpp"
#include "MyShot.hpp"
#include "MedChargeLaser.hpp"
#include "MaxChargeLaser.hpp"
#include <vector>

using namespace std;
int xpos[3] = {500, 550, 600};
int sprites[4][2] = {{0, 0}, {30, 0}, {0, 30}, {30, 30}};

// top viewport for score
SDL_Rect topViewport;
//bottom viewport where the game is played
SDL_Rect bottomViewport;
// background space texture
MyTexture gSpaceTexture;

//the main window
SDL_Window* gWindow = NULL;
//the main screen surface
SDL_Surface* gScreenSurface = NULL;
//a test image
SDL_Surface* gTestImg = NULL;
// renderer
SDL_Renderer* gRenderer = NULL;

// Textures
MyTexture spaceTexture;
MyTexture blueTexture;
MyTexture shipMedTexture;
MyTexture shipMaxTexture;
MyTexture blueHurtTexture;
MyTexture batteryTexture;
MyTexture redTexture;
MyTexture straightTexture;
MyTexture laserTexture;
MyTexture sprLaserTexture;
MyTexture medChargeTexture;
MyTexture maxChargeTexture;
MyTexture badLaserTexture;
MyTexture homingLaserTexture;
MyTexture homingTexture;
MyTexture homingHurtTexture;
MyTexture homingSpawnTexture;
MyTexture spreadTexture;
MyTexture spreadHurtTexture;
MyTexture orbiterTexture;
MyTexture orbiterHurtTexture;

// Game font
TTF_Font* gFont = NULL;

// Text-related textures
MyTexture textTexture;
MyTexture timerTexture;
MyTexture waveTexture;
MyTexture scoreTexture;
MyTexture startTexture;
MyTexture successTexture;
MyTexture failureTexture;

// Power-up textures (battery shares same texture as life icon)
MyTexture shieldTexture;
MyTexture sprshotTexture;
MyTexture pierceTexture;
MyTexture chargeTexture;
MyTexture bubbleShieldTexture;

// Useless (for now)
MyMouseButton buttonOne;

// Funky (regular level) music
Mix_Music *music = NULL;

// Stringstreams for time, wave, score texts
std::stringstream timeText;
std::stringstream waveText;
std::stringstream scoreText;

//shot cooldown timer
MyTimer shotCooldown;

// The ship the player controls
Player ship;

// Game variables:
bool quit = false;
// current wave
Wave currentWave(0);
// wave number of current wave
int waveNum = 0;
// subwave number of current wave
int subWaveNum = 0;
// how many subwaves are in this wave
int subWavesThisWave = 0;
// player score
int playerScore = 0;
// player shots this wave
vector<MyShot*> myShots;
// enemy shots this wave
vector<Shot*> enemyShots;

//powerups on screen
vector<PowerUp*> powerups;
// is the game started
bool gameStarted = false;
// player shots on screen
int shotsOnScreen = 0;
// is the wave over
bool waveOver = true;
bool isCharging = false;
MyTimer chargeTimer;


// angle for all rotating objects
double angle = 0.0;
// color for all text
SDL_Color textColor = {0, 255, 0, 0};

// Loads background space texture
bool loadMediaTextures(SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, MyTexture* spaceTexture) {
    bool success = true;
    if((*spaceTexture).loadFromFile("SDL_Game/space.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load texture.");
        success = false;
    } else {
        (*spaceTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    return success;
}

// Loads blue texture for ship
bool loadBlueTextures(SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, MyTexture* blueTexture, MyTexture* blueHurtTexture, MyTexture* batteryTexture, MyTexture* shipMedTexture, MyTexture* shipMaxTexture) {
    bool success = true;
    if((*blueTexture).loadFromFile("SDL_Game/finalShip.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load blue texture.");
        success = false;
    } else {
        (*blueTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if((*blueHurtTexture).loadFromFile("SDL_Game/ShipHurt.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load blue texture.");
        success = false;
    } else {
        (*blueHurtTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if((*batteryTexture).loadFromFile("SDL_Game/Battery.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load blue texture.");
        success = false;
    } else {
        (*batteryTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if((*shipMaxTexture).loadFromFile("SDL_Game/ShipMaxCharge.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load blue texture.");
        success = false;
    } else {
        (*shipMaxTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*shipMedTexture).loadFromFile("SDL_Game/ShipMedCharge.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load blue texture.");
        success = false;
    } else {
        (*shipMedTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    return success;
}

// Loads yellow texture for laser and green texture for enemy laser
bool loadLaserTextures(SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, MyTexture* laserTexture, MyTexture* badLaserTexture, MyTexture* homingLaserTexture, MyTexture* sprLaserTexture, MyTexture* medChargeTexture, MyTexture* maxChargeTexture) {
    bool success = true;
    if((*laserTexture).loadFromFile("SDL_Game/laser.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load laser texture.");
        success = false;
    } else {
        (*laserTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*badLaserTexture).loadFromFile("SDL_Game/green-small.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load bad laser texture.");
        success = false;
    } else {
        (*badLaserTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*homingLaserTexture).loadFromFile("SDL_Game/pinkhb.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load bad laser texture.");
        success = false;
    } else {
        (*homingLaserTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*sprLaserTexture).loadFromFile("SDL_Game/SpreadLaser.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load bad laser texture.");
        success = false;
    } else {
        (*sprLaserTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if((*medChargeTexture).loadFromFile("SDL_Game/medCharge.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load bad laser texture.");
        success = false;
    } else {
        (*medChargeTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if((*maxChargeTexture).loadFromFile("SDL_Game/maxCharge.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load bad laser texture.");
        success = false;
    } else {
        (*maxChargeTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    return success;
}

// Loads textures for enemy ships
bool loadRedTextures(SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, MyTexture* redTexture, MyTexture* straightTexture, MyTexture* homingTexture, MyTexture* homingSpawnTexture, MyTexture* homingHurtTexture, MyTexture* spreadTexture, MyTexture* spreadHurtTexture, MyTexture* orbiterTexture, MyTexture* orbiterHurtTexture) {
    bool success = true;
    if((*redTexture).loadFromFile("SDL_Game/finalAsteroid.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*redTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*straightTexture).loadFromFile("SDL_Game/finalStraight.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*straightTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*homingTexture).loadFromFile("SDL_Game/HomingTurret.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*homingTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*homingSpawnTexture).loadFromFile("SDL_Game/TurretSpawn.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*homingSpawnTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*homingHurtTexture).loadFromFile("SDL_Game/HomingTurretHurt.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*homingHurtTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*spreadTexture).loadFromFile("SDL_Game/SpreadShooter.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*spreadTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*spreadHurtTexture).loadFromFile("SDL_Game/SpreadShooterHurt.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*spreadHurtTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*orbiterTexture).loadFromFile("SDL_Game/Orbiter.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*orbiterTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*orbiterHurtTexture).loadFromFile("SDL_Game/OrbiterHurt.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*orbiterHurtTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    return success;
}

// Loads font for text
bool loadTextTextures(SDL_Renderer** gRenderer, MyTexture* textTexture, MyTexture* timerTexture, MyTexture* startTexture, MyTexture* successTexture, MyTexture* failureTexture, TTF_Font** gFont) {
    bool success = true;
    *gFont = TTF_OpenFont("SDL_Game/Quinque.ttf", 28);
    if(*gFont == NULL) {
        printf("Could not load font.\n");
        success = false;
    } else {
        SDL_Color textColor = {0, 255, 0, 0};
        if((*textTexture).loadFromText("SCORE: ", gRenderer, textColor, gFont) == false) {
            printf("Failed to render text texture.\n");
            success = false;
        }
        
        if((*timerTexture).loadFromText("Press enter", gRenderer, textColor, gFont) == false) {
            printf("Failed to render timer texture.\n");
            success = false;
        }
        
        if((*startTexture).loadFromText("Press Space", gRenderer, textColor, gFont) == false) {
            printf("Failed to render start texture.\n");
            success = false;
        }
        
        if((*successTexture).loadFromText("Next wave!", gRenderer, textColor, gFont) == false) {
            printf("Failed to render success texture.\n");
            success = false;
        }
        
        if((*failureTexture).loadFromText("Game Over", gRenderer, textColor, gFont) == false) {
            printf("Failed to render failure texture.\n");
            success = false;
        }
        
    }
    return success;
}

// Loads textures for powerups
bool loadPowerTextures(SDL_Surface** gScreenSurface, SDL_Renderer** gRenderer, MyTexture* shieldTexture, MyTexture* spreadTexture, MyTexture* pierceTexture, MyTexture* chargeTexture, MyTexture* bubbleShieldTexture) {
    bool success = true;
    
    if((*shieldTexture).loadFromFile("SDL_Game/Shield.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*shieldTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*spreadTexture).loadFromFile("SDL_Game/Spread.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*spreadTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*pierceTexture).loadFromFile("SDL_Game/Spear.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*pierceTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*chargeTexture).loadFromFile("SDL_Game/Scharge.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*chargeTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    if((*bubbleShieldTexture).loadFromFile("SDL_Game/BubbleShield.png", gScreenSurface, gRenderer, false) == false) {
        printf("Failed to load red texture.");
        success = false;
    } else {
        (*bubbleShieldTexture).setBlendMode(SDL_BLENDMODE_BLEND);
    }
    
    return success;
}

// Loads music
bool loadMusic(Mix_Music** gMusic) {
    bool success = true;
    *gMusic = Mix_LoadMUS("SDL_Game/funky.wav");
    if(*gMusic == NULL) {
        printf("Failed to load funky.wav.\n");
        success = false;
    }
    return success;
}

// Attempts to load all resources necessary. Could condense into one function but that would be too trivial and I am too lazy to do that.

void initializeGame() {
    // attempt to open window
    if(init(&gWindow, &gScreenSurface, &gRenderer) == false) {
        printf("Could not open window.");
        exit(-1);
    }
    
    // attempt to load space texture
    if(loadMediaTextures(&gScreenSurface, &gRenderer, &spaceTexture) == false) {
        printf("Unable to load media. ");
        exit(-1);
    }
    
    // attempt to load ship texture
    if(loadBlueTextures(&gScreenSurface, &gRenderer, &blueTexture, &blueHurtTexture, &batteryTexture, &shipMedTexture, &shipMaxTexture) == false) {
        printf("Unable to load blue. ");
        exit(-1);
    }
    
    // attempt to load enemy texture
    if(loadRedTextures(&gScreenSurface, &gRenderer, &redTexture, &straightTexture, &homingTexture, &homingSpawnTexture, &homingHurtTexture, &spreadTexture, &spreadHurtTexture, &orbiterTexture, &orbiterHurtTexture) == false) {
        printf("Unable to load red.\n");
        exit(-1);
    }
    
    // attempt to load laser textures
    if(loadLaserTextures(&gScreenSurface, &gRenderer, &laserTexture, &badLaserTexture, &homingLaserTexture, &sprLaserTexture, &medChargeTexture, &maxChargeTexture) == false) {
        printf("Unable to load laser.\n");
        exit(-1);
    }
    
    // attempt to load text textures
    if(loadTextTextures(&gRenderer, &textTexture, &timerTexture, &startTexture, &successTexture, &failureTexture, &gFont) == false) {
        printf("Unable to load font.\n");
        exit(-1);
    }
    
    if(loadPowerTextures(&gScreenSurface, &gRenderer, &shieldTexture, &sprshotTexture, &pierceTexture, &chargeTexture, &bubbleShieldTexture) == false) {
        printf("Unable to load powerup textures.\n");
        exit(-1);
    }
    
    // attempt to load music
    if(loadMusic(&music) == false) {
        printf("Couldn't load music.\n");
        exit(-1);
    }
}

// pregame loop stuff, pretty self-explanatory
void repeatNotStarted(SDL_Event* e) {
    Mix_HaltMusic();
    while(SDL_PollEvent(e)) {
        if(e->type == SDL_QUIT) {
            quit = true;
        }
        
        if(e->key.keysym.sym == SDLK_SPACE) {
            gameStarted = true;
        }
        
        refreshCyclePregame(&gRenderer, topViewport, bottomViewport, &spaceTexture, &startTexture);
        SDL_RenderPresent(gRenderer);
    }
}

// "End-game" process that happens on a game over
void gameOver() {
    Mix_HaltMusic();
    ship.reset();
    playerScore = 0;
    if(isCharging) {
        isCharging = false;
    }
    if(chargeTimer.isStarted()) {
        chargeTimer.stop();
    }
    waveNum = 0;
    myShots.clear();
    for(int i = 0; i < myShots.size(); i++) {
        delete myShots[i];
    }
    enemyShots.clear();
    for(int i = 0; i < enemyShots.size(); i++) {
        delete enemyShots[i];
    }
    for(int i = 0; i < powerups.size(); i++) {
        delete powerups[i];
    }
    powerups.clear();
    currentWave.endWave();
    SDL_RenderSetViewport(gRenderer, &bottomViewport);
    failureTexture.render(0, 0, &gRenderer);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    gameStarted = false;
    currentWave = Wave(0);
    waveOver = true;
}

// render everything on screen

void renderAll() {
    
        // render ship with correct sprite if is hit or not
    if(ship.getHit()) {
        ship.render(&blueHurtTexture, &gRenderer, 0.0);
    } else {
        if(ship.getMode() == 4) {
            if(chargeTimer.getTicks() < 1000) {
                ship.render(&blueTexture, &gRenderer, 0.0);
            } else if (chargeTimer.getTicks() < 2000) {
                ship.render(&shipMedTexture, &gRenderer, 0.0);
            } else {
                ship.render(&shipMaxTexture, &gRenderer, 0.0);
            }
        } else {
            ship.render(&blueTexture, &gRenderer, 0.0);
        }
    }
    
    // render shield with correct sprite if applicable
    if(ship.getMode() == 1) {
        Uint64 ticks = SDL_GetTicks64();
        int sprite = (ticks / 100) % 4;
        bubbleShieldTexture.renderPart(ship.getRect().x, ship.getRect().y, &gRenderer, sprites[sprite][0], sprites[sprite][1], 30, 30);
    }

    SDL_RenderSetViewport(gRenderer, &topViewport);

    for(int i = 0; i < ship.getHp(); i++) {
        batteryTexture.render(xpos[i], 10, &gRenderer);
    }
    
    if(ship.getMode() == 1) {
        shieldTexture.render(500, 45, &gRenderer);
    } else if(ship.getMode() == 2) {
        sprshotTexture.render(500, 45, &gRenderer);
    } else if(ship.getMode() == 3) {
        pierceTexture.render(500, 45, &gRenderer);
    } else if(ship.getMode() == 4) {
        chargeTexture.render(500, 45, &gRenderer);
    }

    SDL_RenderSetViewport(gRenderer, &bottomViewport);
    
    // render all still-alive enemies
    for(int i = 0; i < currentWave.getBaddies()[subWaveNum].size(); i++) {
        if(currentWave.getBaddies()[subWaveNum][i]->getDead() == false) {
            if(currentWave.getBaddies()[subWaveNum][i]->getType() == 0) {
                currentWave.getBaddies()[subWaveNum][i]->render(&redTexture, &gRenderer, angle);
            } else if (currentWave.getBaddies()[subWaveNum][i]->getType() == 1) {
                // STRAIGHT SHOOTER
                currentWave.getBaddies()[subWaveNum][i]->render(&straightTexture, &gRenderer, angle);
            } else if (currentWave.getBaddies()[subWaveNum][i]->getType() == 2) {
                // HOMING TURRET
                if(((HomingTurret*)currentWave.getBaddies()[subWaveNum][i])->getSpawned()) {
                    // if is spawned
                    if(currentWave.getBaddies()[subWaveNum][i]->getHit()) {
                        currentWave.getBaddies()[subWaveNum][i]->render(&homingHurtTexture, &gRenderer, angle);
                    } else {
                        currentWave.getBaddies()[subWaveNum][i]->render(&homingTexture, &gRenderer, angle);
                    }
                } else {
                    // if not spawned yet
                    currentWave.getBaddies()[subWaveNum][i]->render(&homingSpawnTexture, &gRenderer, angle);
                }
            } else if (currentWave.getBaddies()[subWaveNum][i]->getType() == 3) {
                // SPREAD SHOOTER
                if(currentWave.getBaddies()[subWaveNum][i]->getHit()) {
                    currentWave.getBaddies()[subWaveNum][i]->render(&spreadHurtTexture, &gRenderer, angle);
                } else {
                    currentWave.getBaddies()[subWaveNum][i]->render(&spreadTexture, &gRenderer, angle);
                }
            } else if (currentWave.getBaddies()[subWaveNum][i]->getType() == 4) {
                // ORBITER
                if(currentWave.getBaddies()[subWaveNum][i]->getHit()) {
                    currentWave.getBaddies()[subWaveNum][i]->render(&orbiterHurtTexture, &gRenderer, angle);
                } else {
                    currentWave.getBaddies()[subWaveNum][i]->render(&orbiterTexture, &gRenderer, angle);
                }
            }
        }
    }
    // render all still onscreen shots
    
    for(int i = 0; i < myShots.size(); i++) {
        if(myShots[i]->getOnscreen()) {
            myShots[i]->render(&gRenderer);
        }
    }
    

        // render all still onscreen enemy shots
    for(int i = 0; i < enemyShots.size(); i++) {
        if(enemyShots[i]->getOnscreen()) {
            if(enemyShots[i]->getType() == 0) {
                enemyShots[i]->render(&badLaserTexture, &gRenderer);
            } else if (enemyShots[i]->getType() == 1) {
                enemyShots[i]->render(&homingLaserTexture, &gRenderer);
            }
        }
    }

    // render all still active powerups
    for(int i = 0; i < powerups.size(); i++) {
        if(powerups[i]->getActive()) {
            powerups[i]->render(&gRenderer);
        }
    }
}

// Schmoovin and groovin
void moveAll() {
    
    // Move all enemies, have them shoot if necessary
    for(int i = 0; i < currentWave.getBaddies()[subWaveNum].size(); i++) {
        if(currentWave.getBaddies()[subWaveNum][i]->getDead() == false) {
            currentWave.getBaddies()[subWaveNum][i]->move(ship.getRect());
            currentWave.getBaddies()[subWaveNum][i]->shoot(ship.getRect(), enemyShots);
        }
    }
    
    // Move all player shots
 
    
    for(int i = 0; i < myShots.size(); i++) {
        if(myShots[i]->getOnscreen()) {
            myShots[i]->move();
        }
    }
    
    // Move all enemy shots
    for(int i = 0; i < enemyShots.size(); i++) {
        if(enemyShots[i]->getOnscreen()) {
            enemyShots[i]->move(ship.getRect());
        }
    }

    
    // Move all powerups
    for(int i = 0; i < powerups.size(); i++) {
        if(powerups[i]->getActive()) {
            powerups[i]->move();
        }
    }
    
    // Move ship
    ship.move();
}

//what to do when the wave ends
void endWave() {
    myShots.clear();
    for(int i = 0; i < myShots.size(); i++) {
        delete myShots[i];
    }
    enemyShots.clear();
    for(int i = 0; i < enemyShots.size(); i++) {
        delete enemyShots[i];
    }
    // frees necessary memory of wave objects + powerups
    currentWave.endWave();
    for(int i = 0; i < powerups.size(); i++) {
        delete powerups[i];
    }
    powerups.clear();
    // sets subwave num to 0, increases wave num
    waveNum++;
    subWaveNum = 0;
    if(isCharging) {
        isCharging = false;
    }
    if(chargeTimer.isStarted()) {
        chargeTimer.stop();
    }
    // "refresh" screen
    refreshCycle(&gRenderer, topViewport, bottomViewport, &angle, &spaceTexture, &textTexture, &waveTexture, &scoreTexture);
    SDL_RenderSetViewport(gRenderer, &bottomViewport);
    // render "next wave" screen
    successTexture.render(0, 0, &gRenderer);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    successTexture.render(0, 0, &gRenderer);
    // create new wave, assign appropriate value to subwaves variable, sets wave as not over
    currentWave = Wave(waveNum);
    subWavesThisWave = (int)(currentWave.getBaddies().size());
    waveOver = false;
}

// Renders wave + score text
void renderText() {
    waveText.str("");
    waveText << "Wave: " << waveNum;
    
        // Attempt to render wave text texture
    if(!waveTexture.loadFromText(waveText.str().c_str(), &gRenderer, textColor, &gFont)) {
        printf("Couldn't render wave texture.\n");
    }
    
        // Ditto, but with score text
    scoreText.str("");
    scoreText << "Score: " << playerScore;
    
    if(!scoreTexture.loadFromText(scoreText.str().c_str(), &gRenderer, textColor, &gFont)) {
        printf("Couldn't render score texture.\n");
    }
}

void handlePowerups() {
    if(waveOver == false) {
        for(int i = 0; i < powerups.size(); i++) {
            if(powerups[i]->getActive()) {
                SDL_Rect r1 = powerups[i]->getRect();
                SDL_Rect r2 = ship.getRect();
                if(SDL_HasIntersection(&r1, &r2) == SDL_TRUE) {
                    powerups[i]->takeEffect(ship);
                }
            }
        }
    }
}

void handleKeyPresses(SDL_Event* e) {
    // handle closing the window
    if(e->type == SDL_QUIT) {
        quit = true;
    }
    // handle various button presses
    if (e->type == SDL_KEYDOWN) {
        if(e->key.keysym.sym == SDLK_m) {
            if(Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(music, -1);
            } else {
                if(Mix_PausedMusic() == 1) {
                    Mix_ResumeMusic();
                } else {
                    Mix_PauseMusic();
                }
            }
        }
    }
    
    // ship responds to directional input
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    ship.handleEvent(*e);
    // handles shooting w/ cooldown
    if(keystate[SDL_SCANCODE_SPACE]) {
        // TODO: REMOVE LAST "OR" WHEN CHARGE IS IMPLEMENTED
        if(ship.getMode() == 0 || ship.getMode() == 1 || ship.getMode() == 3) {
            // Normal / shield / pierce powerup
            if(shotCooldown.getTicks() >= 500 && shotsOnScreen < 5) {
                shotCooldown.start();
                myShots.push_back(new GoodLaser(&laserTexture, ship.getRect().x + 15, ship.getRect().y + 15));
            }
        } else if (ship.getMode() == 2) {
            if(shotCooldown.getTicks() >= 500) {
                shotCooldown.start();
                myShots.push_back(new SpreadLaser(&sprLaserTexture, ship.getRect().x + 15, ship.getRect().y + 15, 5, 0));
                myShots.push_back(new SpreadLaser(&sprLaserTexture, ship.getRect().x + 15, ship.getRect().y + 15, 3, 4));
                myShots.push_back(new SpreadLaser(&sprLaserTexture, ship.getRect().x + 15, ship.getRect().y + 15, 3, -4));
            }
        } else if (ship.getMode() == 4) {
            // Charge powerup
            if(!chargeTimer.isStarted()) {
                chargeTimer.start();
            }
            if(!isCharging) {
                isCharging = true;
            }
        }
        
    } else {
        //cout << chargeTimer.getTicks() << "\n";
        if(ship.getMode() == 4) {
            if(chargeTimer.isStarted()) {
                if(shotCooldown.getTicks() >= 500) {
                    shotCooldown.start();
                    if(chargeTimer.getTicks() < 1000) {
                        myShots.push_back(new GoodLaser(&laserTexture, ship.getRect().x + 15, ship.getRect().y + 15));
                    } else if(chargeTimer.getTicks() < 2000) {
                        myShots.push_back(new MedChargeLaser(&medChargeTexture, ship.getRect().x + 15, ship.getRect().y + 15));
                    } else {
                        myShots.push_back(new MaxChargeLaser(&maxChargeTexture, ship.getRect().x + 15, ship.getRect().y - 5));
                    }
                }
                chargeTimer.stop();
                isCharging = false;
            }
        }
    }
    
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        if (e->key.keysym.sym == SDLK_ESCAPE) {
            //TODO: Pause menu goes here.
            Mix_HaltMusic();
        }
    }
}


void handleHitEnemy() {
    for(int i = 0; i < currentWave.getBaddies()[subWaveNum].size(); i++) {
        if(currentWave.getBaddies()[subWaveNum][i]->getDead() == false) {
            // special case for un-spawned HomingTurrets
            if(currentWave.getBaddies()[subWaveNum][i]->getType() == 2 && ((HomingTurret*)currentWave.getBaddies()[subWaveNum][i])->getSpawned() == false) {
                
            } else {
                SDL_Rect r1 = currentWave.getBaddies()[subWaveNum][i]->getRect();
                SDL_Rect r2 = ship.getRect();
                if(SDL_HasIntersection(&r1, &r2) == SDL_TRUE && ship.getHit() == false) {
                    ship.kill(&spaceTexture, &gRenderer);
                    ship.onHit();
                    if(ship.getAlive() == false) {
                        gameOver();
                        break;
                    }
                }
            }
        }
    }
}

void handleHitShot() {
    if(ship.getAlive() == true) {
        for(int i = 0; i < enemyShots.size(); i++) {
            if(enemyShots[i]->getOnscreen() == true) {
                SDL_Rect r1 = enemyShots[i]->getRect();
                SDL_Rect r2 = ship.getRect();
                if(SDL_HasIntersection(&r1, &r2) == SDL_TRUE && ship.getHit() == false) {
                    ship.kill(&spaceTexture, &gRenderer);
                    ship.onHit();
                    if(ship.getAlive() == false) {
                        gameOver();
                        break;
                    }
                }
            }
        }
    }
}

// code handling what happens when you shoot an enemy
void handleShootEnemy() {
    for(int i = 0; i < myShots.size(); i++) {
        if(myShots[i]->getOnscreen() && waveOver == false) {
            for(int j = 0; j < currentWave.getBaddies()[subWaveNum].size(); j++) {
                
                SDL_Rect r1 = myShots[i]->getRect();
                SDL_Rect r2 = currentWave.getBaddies()[subWaveNum][j]->getRect();
                
                // if shot hits an enemy
                if(currentWave.getBaddies()[subWaveNum][j]->getDead() == false && SDL_HasIntersection(&r1, &r2) == SDL_TRUE) {
                    
                    if(currentWave.getBaddies()[subWaveNum][j]->getType() != 2) {
                        // hit this enemy, increment player score, drop powerups if needed
                        if(currentWave.getBaddies()[subWaveNum][j]->willDrop() && currentWave.getBaddies()[subWaveNum][j]->getHit() == false) {
                            switch(currentWave.getBaddies()[subWaveNum][j]->itemDrop()) {
                                case 1: {
                                    powerups.push_back(new ShieldPow(&shieldTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    break;
                                }
                                case 2: {
                                    powerups.push_back(new SpreadPow(&sprshotTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    break;
                                }
                                case 3: {
                                    powerups.push_back(new PiercePow(&pierceTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    break;
                                }
                                case 4: {
                                    powerups.push_back(new  LifePow(&batteryTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    break;
                                }
                                case 5: {
                                    powerups.push_back(new ChargePow(&chargeTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    break;
                                }

                            }

                        }
                        currentWave.getBaddies()[subWaveNum][j]->onHit();
                        currentWave.getBaddies()[subWaveNum][j]->kill(&spaceTexture, &gRenderer);
                        if(ship.getMode() != 3) {
                            myShots[i]->kill(&spaceTexture, &gRenderer);
                        }
                        if(currentWave.getBaddies()[subWaveNum][j]->getDead()) {
                            playerScore += 10;
                        }
                    } else {
                        if(((HomingTurret*)currentWave.getBaddies()[subWaveNum][j])->getSpawned()) {
                            if(currentWave.getBaddies()[subWaveNum][j]->willDrop() && currentWave.getBaddies()[subWaveNum][j]->getHit() == false) {
                                switch(currentWave.getBaddies()[subWaveNum][j]->itemDrop()) {
                                    case 1: {
                                        powerups.push_back(new ShieldPow(&shieldTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    }
                                    case 2: {
                                        powerups.push_back(new SpreadPow(&sprshotTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    }
                                    case 3: {
                                        powerups.push_back(new PiercePow(&pierceTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    }
                                    case 4: {
                                        powerups.push_back(new  LifePow(&batteryTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    }
                                    case 5: {
                                        powerups.push_back(new ChargePow(&chargeTexture, currentWave.getBaddies()[subWaveNum][j]->getRect().x, currentWave.getBaddies()[subWaveNum][j]->getRect().y));
                                    }

                                }

                            }
                            currentWave.getBaddies()[subWaveNum][j]->onHit();
                            currentWave.getBaddies()[subWaveNum][j]->kill(&spaceTexture, &gRenderer);
                            if(ship.getMode() != 3) {
                                myShots[i]->kill(&spaceTexture, &gRenderer);
                            }
                            if(currentWave.getBaddies()[subWaveNum][j]->getDead()) {
                                playerScore += 10;
                            }
                        }
                    }
                    bool subWaveOver = true;
                    // if all enemies in subwave dead, this subwave is over
                    for(int k = 0; k < currentWave.getBaddies()[subWaveNum].size(); k++) {
                        if(currentWave.getBaddies()[subWaveNum][k]->getDead() == false) {
                            subWaveOver = false;
                        }
                    }
                    //if subwave is over, increment subwave number
                    if(subWaveOver == true) {
                        subWaveNum++;
                    }
                    waveOver = true;
                    // if subwave number >= subwaves this wave, wave is over
                    if (subWaveNum < subWavesThisWave) {
                        waveOver = false;
                    } else {
                        subWaveNum--;
                    }
                    break;
                }
            }
        }
    }
}

// Main function, includes game loop
int main(int argc, const char * argv[]) {
    
    // set seed for randomization
    srand(time(0));
    
    //set viewport positions + dimensions
    topViewport.x = 0;
    topViewport.y = 0;
    topViewport.w = SCREEN_WIDTH;
    topViewport.h = SCREEN_HEIGHT / 5;
    bottomViewport.x = 0;
    bottomViewport.y = (SCREEN_HEIGHT / 5);
    bottomViewport.w = SCREEN_WIDTH;
    bottomViewport.h = (SCREEN_HEIGHT / 5) * 4;
    
    initializeGame();

    // event we are polling for
    SDL_Event e;
    // "refresh" the screen
    refreshCycle(&gRenderer, topViewport, bottomViewport, &angle, &spaceTexture, &textTexture, &waveTexture, &scoreTexture);

    // display stuff to screen
    SDL_RenderSetViewport(gRenderer, &bottomViewport);
    SDL_RenderPresent(gRenderer);
    // whether the game has been quit
    
    while(!quit) {
        
        if(gameStarted == true) {
            // start the shot cooldown timer
            if(!shotCooldown.isStarted()) {
                shotCooldown.start();
            }
            
            // Event poll loop HERE
            while(SDL_PollEvent(&e)) {
                handleKeyPresses(&e);
            }
            
            if(waveOver) {
                endWave();
            }
            moveAll();
            // Refresh wave text
            renderText();
            // "Refresh" screen
            refreshCycle(&gRenderer, topViewport, bottomViewport, &angle, &spaceTexture, &textTexture, &waveTexture, &scoreTexture);
            renderAll();
            // handle touching powerups
            handlePowerups();
            
            // handle shots hitting enemies + spawning powerups if applicable
            handleShootEnemy();
            
            if(waveOver == false) {
                // hitting enemy
                handleHitEnemy();
                handleHitShot();
            }
            
            SDL_RenderPresent(gRenderer);
            if(Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(music, -1);
            }
        } else {
            repeatNotStarted(&e);
        }
    }
    close(&gWindow, &gTestImg, &gRenderer, &music);
    spaceTexture.free();
    return 0;
}
