// Phos - Simple space shooter for the Arduboy
// Code by Dial - Art by Schuss
// https://github.com/DLeinHellios/arduboy-phos

#include "globals.h"
#include "game.h"
#include "menu.h"
#include "endgame.h"

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(GAME_FPS);
    arduboy.audio.off();
    initStars();
}

void loop() {
    if (!arduboy.nextFrame()) {return;}
    arduboy.clear();

    //---- Menu Screen ----
    if (gameState == 0) {
        menuFrame();
    }

    //---- Game Active ----
    if (gameState == 1)  {
        gameFrame();
    }

    //---- Game Pause ----
    if (gameState == 2) {
        pauseFrame();
    }

    //---- Game Over ----
    if (gameState == 3)  {
        endgameFrame();
    }

    //---- Game Info ----
    if (gameState == 4)  {
        infoFrame();
    }

    //---- Credits ----
    if (gameState == 5)  {
        creditsFrame();
    }

    arduboy.display();
}
