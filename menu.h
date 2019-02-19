#ifndef MENU_H
#define MENU_H


// ==================== Menu Functions ====================


void menuEvents() { //Handles menu options
    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))  {
        sound.noTone();
        startGame();
    }

    if (arduboy.justPressed(UP_BUTTON))  {
        gameState = 4;
    }

    if (arduboy.justPressed(DOWN_BUTTON))  {
        gameState = 5;
    }

    if (arduboy.justPressed(LEFT_BUTTON))  {
        if (arduboy.audio.enabled())  {
            // Disable
            arduboy.audio.off();
            sound.noTone();
        } else  {
            // Enable
            arduboy.audio.on();
            lastLifeSound();
        }
    }
}


void updateMenuEnemies()  {
    // Moves enemies for decorative use
    for (int i = 0; i < ENEMY_MAX_SPAWNS; i++)  {
        enemyArray[i].update();
    }
}


void menuUpdate() {
      spawnEnemies(60);
      updateMenuEnemies();
      updateStars();
}


void drawTitle()  {
    // Handles title animation
    animationCounter += 1;
    int nFrames = 5;
    if(animationCounter >= TITLE_FREQ) {
        if(titleFrame < nFrames) {
            if(animationCounter % 2 == 0) {
                titleFrame += 1;
            }
        } else if(animationCounter % 2 == 0) {
            animationCounter = 0;
            titleFrame = 0;
        }
    }
    sprites.drawOverwrite(39,0,titleSprites,titleFrame);
}


void drawContents()  {
    //Draws available menu actions
    sprites.drawSelfMasked(33,24,menuContent,0);
    sprites.drawExternalMask(94,39,soundSprite,soundMask,arduboy.audio.enabled(),0);
}


void menuDraw() {
    drawTitle();
    drawEnemies();
    drawStars();
    drawContents();
}


void menuFrame() {
    //Conducts one frame of main menu
    menuEvents();
    menuUpdate();
    menuDraw();
}


//==================== Page Functions ====================


// ---- Pause ----
void pauseEvents()  {
    arduboy.pollButtons();
    if (arduboy.justPressed(A_BUTTON))  {
        gameState = 1;
    }
}


void drawPause()  {
    gameDraw();
    arduboy.fillRect(49,27,31,8,BLACK);
    sprites.drawOverwrite(50,28,pausedText,0);
}


void pauseFrame() {
    // Conducts one frame of pause screen
    pauseEvents();
    drawPause();
}


// ---- Game Information ----
void drawInfo()  {
    sprites.drawExternalMask(14,9,dpadSprite,dpadMask,0,0);
    sprites.drawExternalMask(77,13,btnSprite,btnMask,0,0);

    // Up
    arduboy.drawLine(35,9,35,6);
    arduboy.drawLine(15,6,34,6);
    arduboy.drawLine(6,12,6,30);
    arduboy.drawLine(7,30,13,30);
    sprites.drawSelfMasked(3,3,infoText,0);

    // Down
    arduboy.drawLine(35,52,35,55);
    arduboy.drawLine(36,55,54,55);
    arduboy.drawLine(57,30,62,30);
    arduboy.drawLine(63,30,63,48);
    sprites.drawSelfMasked(59,51,infoText,1);

    // Shoot
    arduboy.drawLine(112,20,118,20);
    arduboy.drawLine(118,21,118,45);
    arduboy.drawLine(117,45,110,45);
    sprites.drawSelfMasked(84,41,infoText,2);

    // Pause
    arduboy.drawLine(76,26,71,26);
    arduboy.drawLine(71,25,71,7);
    arduboy.drawLine(72,7,79,7);
    sprites.drawSelfMasked(83,4,infoText,3);
}


void infoFrame() {
    // Conducts one frame of information screen
    updateStars();
    drawStars();
    drawInfo();
    menuExit();
}


// ---- Credits Screen ----
void drawCredits() {
    updateStars();
    sprites.drawOverwrite(38,17,creditsSprite,0);
    drawStars();
}


void creditsFrame() {
    // Conducts one frame of credits screen
    drawCredits();
    menuExit();
}
#endif
