#ifndef ENDGAME_H
#define ENDGAME_H

#include "menu.h"
#include "bitmaps.h"


//==================== Game Over Screen ====================
void drawGameOver() {
    // Handles title animation
    animationCounter += 1;
    int nFrames = 1;
    int frequency = 30;
        if(gameOverFrame < nFrames) {
            if(animationCounter % frequency == 0) {
                gameOverFrame += 1;
            }
        } else if(animationCounter % frequency == 0)    {
            animationCounter = 0;
            gameOverFrame = 0;
        }
    sprites.drawOverwrite(6,6,endgameSprites,gameOverFrame);
}


void drawStats() {
    // Draws stats from completed game
    int x = 20;
    sprites.drawOverwrite(x,33,uiText,0);
    sprites.drawOverwrite(x+27,33,nums,gameStage);
    sprites.drawOverwrite(x+38,33,uiText,1);
    for (int i = 0; i < 5; i++)  {
        sprites.drawOverwrite((x+65)+(5*i),33,nums,gameScoreArray[i]);
    }
}


void drawAccuracy(int n0, int n1) {
    // Draws player accuracy
    int x;
    if(statsFired == 0 || statsHit == 0) {
        x = 40;
        sprites.drawOverwrite(x,44,accuracyText,0);
        sprites.drawOverwrite(x+43,44,nums,0);;
        sprites.drawOverwrite(x+48,44,uiSymbols,1);
    } else if(statsHit == statsFired) {
        x = 33;
        sprites.drawOverwrite(x,44,accuracyText,0);
        sprites.drawOverwrite(x+43,44,nums,1);
        sprites.drawOverwrite(x+48,44,nums,0);
        sprites.drawOverwrite(x+53,44,nums,0);
        sprites.drawOverwrite(x+58,44,uiSymbols,1);
    } else {
        x = 36;
        sprites.drawOverwrite(x,44,accuracyText,0);
        sprites.drawOverwrite(x+43,44,nums,n0);
        sprites.drawOverwrite(x+48,44,nums,n1);
        sprites.drawOverwrite(x+53,44,uiSymbols,1);
    }
}


void drawBorders() {
    // Vertical
    arduboy.drawLine(0,0,0,63);
    arduboy.drawLine(2,2,2,61);
    arduboy.drawLine(127,0,127,63);
    arduboy.drawLine(125,2,125,61);
    // Horizontal
    arduboy.drawLine(0,0,127,0);
    arduboy.drawLine(0,63,127,63);
    arduboy.drawLine(2,2,125,2);
    arduboy.drawLine(2,61,125,61);
}


void endgameFrame() {
    // Conducts one frame of the Game Over screen

    drawGameOver();
    drawStats();
    drawAccuracy(statsAccuracy0,statsAccuracy1);
    drawBorders();

    // Return to menu
    if (waitCounter > 90) {
        menuExit();
    } else {
        waitCounter += 1;
    }

}


#endif
