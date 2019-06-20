#ifndef GLOBALS_H
#define GLOBALS_H


#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <Sprites.h>
#include "constants.h"


Arduboy2Base arduboy;
Sprites sprites;


// -- Game --
int gameState = 0; // Tracks scenes
long gameScore; // Tracks player score
int *gameScoreArray; // Score in array for drawing
int gameStage; // Tracks increasing spawn difficulty

// -- Enemies --
int enemyRates[3] = {40,55,90}; // Tracks enemy spawn rate shift (different ships)
int enemySpawnFrame;  // Tracks enemy spawn speed
bool spawning = true; // Are enemies spawning?
int enemyCounter;  // Counts frames for enemy spawns
int eliteCounter; // Counts frames for elite spawns

// -- Stats --
int statsFired = 0; // # shots fired
int statsHit = 0; // # shots hit
int statsAccuracy0 = 0; // Accuracy int in tens place
int statsAccuracy1 = 0; // Accuracy int in ones place

// -- Progression --
int stageUp; // Holds number of points until stage increase
int spawnUp; // Holds number of kills before enemySpawnFrame decreases
int lifeUp; // Holds number of points to gain a life

// -- Animation --
int animationCounter = 0; // Counts frames for animations
int waitCounter = 0; // Counts frames for waiting
int titleFrame = 0; // Frame of title animation
int deathFrame = 0; // Death frame animation
int deathPos = 0; // y-position of player on death
int gameOverFrame = 0; // Frame of game over animation
int starsX[GAME_MAX_STARS];
int starsY[GAME_MAX_STARS];


#endif
