#ifndef CONSTANTS_H
#define CONSTANTS_H


// Game
#define GAME_FPS 30 // Game framerate
#define GAME_MAX_STARS 15 // Max background stars generated
#define INIT_STAGEUP 350 // Initial value to trigger stage increase
#define MULTIPLY_STAGEUP 300 // Add initial value and multiply by new stage
#define INIT_SPAWNUP 3 // Initial value to increase spawn frequency
#define INIT_LIFEUP 2500 // Point value to gain first life, 2x thereafter
#define DEATH_WAIT_FRAMES 120 // Number of frames before resuming spawning post death

// Player ship
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


#endif
