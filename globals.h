#ifndef GLOBALS_H
#define GLOBALS_H


#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <Sprites.h>


Arduboy2Base arduboy;
Sprites sprites;
ArduboyTones sound(arduboy.audio.enabled);


#include "bitmaps.h"
#include "sounds.h"
#include "ships.h"


// Game
#define GAME_FPS 30 // Game framerate
#define GAME_MAX_STARS 15 // Max background stars generated
#define INIT_STAGEUP 350 // Initial value to trigger stage increase
#define MULTIPLY_STAGEUP 300 // Add initial value and multiply by new stage
#define INIT_SPAWNUP 3 // Initial value to increase spawn frequency
#define INIT_LIFEUP 2500 // Point value to gain first life, 2x thereafter
#define DEATH_WAIT_FRAMES 120 // Number of frames before resuming spawning post death

// Phos (Player ship)
#define PHOS_MIN_Y 8 //Minimum y-coordinate for player ship
#define PHOS_MAX_Y 56 // Maximum y-coordinate for drawing ships
#define PHOS_MAX_SHOTS 3 // Max shots on-screen
#define PHOS_START_LIVES 3 // Starting lives

// Enemies
#define ENEMY_MAX_SPAWNS 15 // Max enemies alive at once
#define ENEMY_MAX_FRAME 55 // Initial enemy spawn frame
#define ENEMY_MIN_FRAME 5 // Minimum frame for enemy spawns
#define ENEMY_DECR_FRAME 5 // Rate to increase enemy spawns
#define ENEMY_DECR_RATES 5 // Rate to increase faster enemy spawns
const int ENEMY_INIT_RATES[3] = {75,90,115}; // Initial rate of enemy spawn velocity
#define ELITE_RATE 500 // Rate to spawn elite enemy, in frames

// Menu
#define TITLE_FREQ 60// Frequency of title animation, in frames

// Variables
int gameState = 0; // Tracks scenes
long gameScore; // Tracks player score
int *gameScoreArray; // Score in array for drawing
int gameStage; // Tracks increasing spawn difficulty

int enemyRates[3] = {40,55,90}; // Tracks enemy spawn rate shift (different ships)
int enemySpawnFrame;  // Tracks enemy spawn speed
bool spawning = true; // Are enemies spawning?
int enemyCounter;  // Counts frames for enemy spawns
int eliteCounter; // Counts frames for elite spawns

int statsFired = 0; // # shots fired
int statsHit = 0; // # shots hit
int statsAccuracy0 = 0; // Accuracy int in tens place
int statsAccuracy1 = 0; // Accuracy int in ones place

int stageUp; // Holds number of points until stage increase
int spawnUp; // Holds number of kills before enemySpawnFrame decreases
int lifeUp; // Holds number of points to gain a life

int animationCounter = 0; // Counts frames for animations
int waitCounter = 0; // Counts frames for waiting
int titleFrame = 0; // Frame of title animation
int deathFrame = 0; // Death frame animation
int deathPos = 0; // y-position of player on death
int gameOverFrame = 0; // Frame of game over animation

// Init Objects and Object-Arrays
Phos phos;
Shot shotArray[PHOS_MAX_SHOTS];
Enemy enemyArray[ENEMY_MAX_SPAWNS];
Elite elite;
int starsX[GAME_MAX_STARS];
int starsY[GAME_MAX_STARS];


//==================== Common Functions ====================


void wipeEnemies() {
    // Kills all enemies, awards no points
    for(int i = 0; i < ENEMY_MAX_SPAWNS; i++) {
        enemyArray[i].killMe();
    }
}


void drawEnemies()  {
    // Iterates over enemy ship array and calls draw
    for (int i = 0; i < ENEMY_MAX_SPAWNS; i++) { //Enemy Ships
        enemyArray[i].draw();
    }
}


void initStars()  {
    // Sets random starting stars
    for (int i = 0; i < GAME_MAX_STARS; i++) {
        starsX[i] = random(1, 128);
        starsY[i] = random(63);
    }
}


void updateStars()  {
    // Updates star positions and spawns
    for (int i = 0; i < GAME_MAX_STARS; i++) {
        starsX[i]--;
        if (starsX[i] < 0) {
            starsX[i] = random(128, 132);
            starsY[i] = random(63);
        }
    }
}


void drawStars()  {
    // Draws star background
    for (int i = 0; i < GAME_MAX_STARS; i++) {
        arduboy.drawPixel(starsX[i], starsY[i]);
    }
}


void menuExit() {
    // Exits pages to main menu
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))  {
        for (int i = 0; i < ENEMY_MAX_SPAWNS; i++) {
            enemyArray[i].killMe();
        }
    animationCounter = 0;
    titleFrame = 0;
    gameState = 0;
    }
}


int * convertScore(long n) {
    // Converts 5-digit long to array of ints
    static int scoreArray[5];

    scoreArray[0] = n / 10000;
    scoreArray[1] = (n / 1000) - ((n / 10000) * 10);
    scoreArray[2] = (n / 100) - ((n / 1000) * 10);
    scoreArray[3] = (n / 10) - ((n / 100) * 10);
    scoreArray[4] = n - ((n / 10) * 10);

    return scoreArray;
}


void checkAccuracy() {
    int accuracy = (int)round((float)statsHit / (float)statsFired * 100);

    statsAccuracy0 = accuracy / 10;
    statsAccuracy1 = accuracy-((accuracy/10)*10);
}


#endif
