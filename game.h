#ifndef GAME_H
#define GAME_H


//==================== Game Functions ====================


void resetValues() {
    // Resets fresh gameplay values
    gameScore = 0;
    gameScoreArray = convertScore(gameScore);
    gameStage = 0;
    stageUp = INIT_STAGEUP;
    spawnUp = INIT_SPAWNUP;
    lifeUp = INIT_LIFEUP;
    enemySpawnFrame = ENEMY_MAX_FRAME;
    statsFired = 0;
    statsHit = 0;
    statsAccuracy0 = 0;
    statsAccuracy1 = 0;
    // Spawn rates
    for(int i = 0; i < 3; i++)  {
        enemyRates[i] = ENEMY_INIT_RATES[i];
    }
}


void resetGame() {
    // Player Reset
    phos.setGameVars(PHOS_START_LIVES);

    // Enemy Reset
    for (int i = 0; i < ENEMY_MAX_SPAWNS; i++) {
        enemyArray[i].killMe();
    }

    // Shot Reset
    for (int i = 0; i < PHOS_MAX_SHOTS; i++) {
        shotArray[i].killMe();
    }
}


void startGame() {
    arduboy.initRandomSeed(); // Seed random number generator
    resetValues();
    resetGame();
    gameState = 1;
}

// ---- Event Handling ----


void shootEvent() {
    // Fires first available shot if < max shots active
    for (int i = 0; i < PHOS_MAX_SHOTS; i++) {
        if (!shotArray[i].checkLife())  {
            shotArray[i].shoot(phos.checkYPos(),phos.isAlive());
            statsFired += 1;
            break;
        }
    }
}


void gameEvents() {
    // Player input handler
    arduboy.pollButtons();

    // Move Up
    if ((arduboy.pressed(UP_BUTTON) || arduboy.pressed(LEFT_BUTTON))) {
        phos.moveUp(PHOS_MIN_Y);
    }

    // Move Down
    if ((arduboy.pressed(DOWN_BUTTON) || arduboy.pressed(RIGHT_BUTTON))) {
        phos.moveDown(PHOS_MAX_Y);
    }

    // Pause
    if ((arduboy.justPressed(A_BUTTON))) {
        gameState = 2;
    }

    // Shoot
    if ((arduboy.justPressed(B_BUTTON))) {
        shootEvent();
    }
}


// ---- Update Variables ----


void spawnEnemies(int enemySpawnFrame)  {
    // Handles spawning of regular enemies, accepts interval between spawns
    enemyCounter++;
    if (enemyCounter >= enemySpawnFrame && spawning) {
        for (int i = 0; i < ENEMY_MAX_SPAWNS; i++) {
            // Activate first available enemy
            if (!enemyArray[i].checkLife())  {
                enemyArray[i].spawn(enemyRates);
                break;
            }
        }
        enemyCounter = 0;
    }
}


void spawnElite(int eliteRate) {
    // Spawns a single elite enemy
    if (eliteCounter >=  eliteRate && spawning && gameStage>0) {
        elite.spawn(gameStage);
        eliteCounter = 0;
    }
    eliteCounter ++;
}


void scoreOverflow() {
    // Prevents score exceeding 99999
    if (gameScore > 99999) {
        gameScore -= 99999;
        gameScoreArray = convertScore(gameScore);
    }
}


void updateShots()  {
    // Moves all live shots forward
    for (int i = 0; i < PHOS_MAX_SHOTS; i++)  {
        shotArray[i].updatePos();
    }
}


void decreaseSpawns() {
    // Increases time between enemy spawns if Phos is hit
    if(enemySpawnFrame + (ENEMY_DECR_FRAME) <= ENEMY_MAX_FRAME) {
        enemySpawnFrame += ENEMY_DECR_FRAME * 2;
        spawnUp = INIT_SPAWNUP;
    }
}


void increaseSpawns()  {
    // Decreases time between spawning enemies when enough enemies killed
    if(spawnUp <= 0 && enemySpawnFrame - ENEMY_DECR_FRAME >= ENEMY_MIN_FRAME) {
        enemySpawnFrame -= ENEMY_DECR_FRAME;
        spawnUp = INIT_SPAWNUP + (((ENEMY_MAX_FRAME/ENEMY_DECR_FRAME) - (enemySpawnFrame/ENEMY_DECR_FRAME)) * 3);
    }
}


void updatePostDeath() {
    // Starts game again following player death
    if(!spawning) {
        if(waitCounter > DEATH_WAIT_FRAMES) {
            spawning = true;
            waitCounter = 0;
        } else if(waitCounter > DEATH_WAIT_FRAMES-30 && !phos.isAlive()) {
            phos.newLife();
            deathFrame = 0;
            if(phos.checkLives() == 1) {
                lastLifeSound();
            }
        } else {
            waitCounter += 1;
        }
    }
}


void updateAllEnemies()  {
    // Normal Enemies
    for (int i = 0; i < ENEMY_MAX_SPAWNS; i++)  {
        if(enemyArray[i].checkLife()) {
            enemyArray[i].update();
        }
    }
    // Elite enemy
    if(elite.checkLife()) {
        elite.update();
    }
}


void increaseStage()  {
    // Progresses game stage as a function of score
    if(gameScore >= stageUp && gameStage < 9)  { // Stage up
        gameStage += 1;
        stageUp += INIT_STAGEUP + (gameStage * MULTIPLY_STAGEUP);
        for(int i =0; i < 3; i++) { // Alter spawn rates
            enemyRates[i] -= ENEMY_DECR_RATES;
        }
    }
}


void getLife() {
    // Adds gained lives and sets up next life-up
    if(gameScore >= lifeUp) {
        phos.addLife();
        lifeUp += INIT_LIFEUP * 2;
    }
}


void checkGameOver() {
    // Moves to game over screen when lives = 0
    if (phos.checkLives() <= 0)  {
        gameScoreArray = convertScore(gameScore);
        checkAccuracy();
        waitCounter = 0;
        animationCounter = 0;
        gameOverFrame = 0;
        gameState = 3;
        sound.noTone();
    }
}


void manageProgress() {
    // Calls all functions that update game progress
    increaseSpawns();
    increaseStage();
    getLife();
    updatePostDeath();
    checkGameOver();
}


void gameUpdate() {
    // Update game variables
    spawnEnemies(enemySpawnFrame);
    spawnElite(ELITE_RATE);
    updateAllEnemies();
    updateShots();
    updateStars();
    manageProgress();
}


// ---- Screen Drawing ----


void drawShots()  {
    // Draw all player bullets
    for (int i = 0; i < PHOS_MAX_SHOTS; i++)  {
        shotArray[i].draw(gameState);
    }
}


void drawLives()  {
    // Draws player lives
    int lives = phos.checkLives();

    if (lives > 6) {
        // Lives > 6
        sprites.drawOverwrite(8,1,uiSymbols,0);
        arduboy.fillRect(12,2,4,2);
        sprites.drawOverwrite(17,-1,nums,lives);

    } else  {
        // Lives <= 6
        for (int i = 0; i < lives - 1; i++) {
            sprites.drawOverwrite((i*5)+2,-1, uiSymbols,0);
        }
    }
}


void drawUIText()  {
    arduboy.fillRect(0,0,128,8,BLACK);
    // Stage
    sprites.drawOverwrite(35,-1,uiText,0);
    sprites.drawOverwrite(63,-1,nums,gameStage);
    // Score
    sprites.drawOverwrite(74,-1,uiText,1);
    for (int i = 0; i < 5; i++)  {
        sprites.drawOverwrite(102+(5*i), -1,nums,gameScoreArray[i]);
    }
}


void drawDeathAnimation() {
    // Draws player death explosion
    animationCounter += 1;
    int nFrames = 3;
    if(animationCounter % 2 == 0) {
        deathFrame += 1;
    }
    if(deathFrame <= nFrames) {
        sprites.drawSelfMasked(0,deathPos-4,phosExplode,deathFrame);
    }
}


void gameDraw()  {
    // Draws entire game screen

    //  Background
    drawStars();

    //  Enemies
    drawEnemies();
    elite.draw();

    //  Player
    drawShots();
    if(phos.isAlive()) {
        phos.draw();
    } else {
        drawDeathAnimation();
    }

    //  Interface
    drawUIText();
    drawLives();
}


// ---- Collision Checking ----


void updateDeath() {
    // Starts player death updates
    deathSound();
    decreaseSpawns();
    deathPos = phos.checkYPos();

    // Delay spawning
    animationCounter = 0;
    waitCounter = 0;
    spawning = false;
}


void checkDeathCollision()  {
    // Iterates over enemies checking collision with player
    for (int i = 0; i < ENEMY_MAX_SPAWNS; i++)  {
        if(enemyArray[i].checkLife() && phos.isHitEnemy(enemyArray[i])) {
            enemyArray[i].killMe();
            updateDeath();
        }
    }

    // Checks elite enemy collision to player
    if(elite.checkLife() && phos.isHitElite(elite)) {
        elite.killMe();
        updateDeath();
    }
}


void updateScore(int points) {
    // Updates score long and converts to array
    gameScore += points;
    scoreOverflow();
    gameScoreArray = convertScore(gameScore);
}


void checkEnemyKill(int points) {
    // Accepts point value from potential kill, manages score and stats
    if (points > 0)  {
        // An enemy was killed
        statsHit += 1;
        spawnUp -= 1;
        updateScore(points);
        enemyKillSound(phos.isAlive());
    }
}


void checkEliteKill(bool eliteHit) {
    // Accepts bool if elite enemy was hit, manages hp, score, and stats
    if(eliteHit) {
        statsHit += 1;
        eliteHitSound(phos.isAlive());
        if(elite.damage()) {
            spawnUp -= 3;
            updateScore((gameStage * 100) + 1);
            eliteKillSound(phos.isAlive());
        }
    }
}


void checkShotCollision() {
    // Iterates over live shots, checking each collision against all enemies
    for (int i = 0; i < PHOS_MAX_SHOTS; i++)  {
        if (shotArray[i].checkLife()) {
            checkEnemyKill(shotArray[i].hitEnemy(enemyArray, ENEMY_MAX_SPAWNS));
            checkEliteKill(shotArray[i].hitElite(elite));
        }
    }
}


void gameCheckCollision() {
    // Checks for all death/kill conditions
    checkShotCollision();
    checkDeathCollision();
}


// =======================================


void gameFrame() {
    // Conducts one frame of gameplay
    gameEvents();
    gameUpdate();
    gameDraw();
    gameCheckCollision();
}


#endif
