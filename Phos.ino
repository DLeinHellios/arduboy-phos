// Phos - Simple space shooter for the Arduboy


#include "globals.h"
#include "game.h"
#include "menu.h"
#include "endgame.h"


void setup() {
    arduboy.begin();
    arduboy.setFrameRate(GAME_FPS);
    initStars();
}


void loop() {
    if (!arduboy.nextFrame()) {return;}
    arduboy.clear();

    switch(gameState) {
        case 0:
            menuFrame();
            break;

        case 1:
            gameFrame();
            break;

        case 2:
            pauseFrame();
            break;

        case 3:
            endgameFrame();
            break;

        case 4:
            infoFrame();
            break;

        case 5:
            creditsFrame();
            break;
    }

    arduboy.display();
}
