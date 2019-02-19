#ifndef CLASSES_H
#define CLASSES_H



class Enemy {
    // Normal Enemy Ship
    private:
        int velocity; // Travel velocity
        int posX; int posY; // Position
        bool isLive = false; // Currently active


    public:
        void spawn(int enemyArray[])  {
            // Spawn action
            int roll = random(1,101);

            // Set Velocity
            if(roll > enemyArray[2]) {
                velocity = 5;
            } else if(roll > enemyArray[1])  {
                velocity = 4;
            } else if(roll > enemyArray[0])  {
                velocity = 3;
            } else {
                velocity = 2;
            }

            // Set position and spawn
            posX = 128;
            posY = random(8, 57);
            isLive = true;
        }


        void update()  {
            if (posX > -5) {
                posX -= velocity;
            } else {
                isLive = false;
            }
        }


        void draw() {
            // Draws live enemy
            if(isLive) {
                sprites.drawSelfMasked(posX,posY,enemySprites,velocity-2);
            }
        }


        int checkVel() {
            // Returns velocity
            return velocity;
        }


        int checkXPos() {
            // Returns x-position
            return posX;
        }


        int checkYPos() {
            // Returns y-position
            return posY;
        }


        bool checkLife() {
            // Returns current alive status
            return isLive;
        }


        void killMe() {
            // Sets enemy as dead
            isLive = false;
        }
};




class Elite {
    // Elite enemy ship
    private:
        int posX;
        int posY;
        int hp;
        int type;
        int yVelocity = 1;
        int stopPos;
        bool isLive = false;
        bool moveUp;


    public:
        void spawn(int stage) {
            if (!isLive) {
                posY = random(8,54);
                posX = 128;
                hp = 3;
                moveUp = random(0,2);
                isLive = true;

                if(stage > 6) {
                    type = 2;
                } else if(stage > 3) {
                    type = 1;
                } else {
                    type = 0;
                }

                hp += type;
                stopPos = 127 - ((type*20) + 50);
            }
        }


        void moveX() {
            // Handles horizontal movement
            if(posX < stopPos) {
                posX -= 2;
            } else {
                posX -= 1;
            }
        }


        void moveY() {
            // Handles vertical movement
            if(posX > stopPos) {
                if(moveUp) {
                    if(posY > 8) {
                        posY -= yVelocity;
                    } else {
                        moveUp = false;
                        yVelocity = random(1,3);
                    }
                } else {
                    if(posY < 54) { // Move down
                        posY += yVelocity;
                    } else { // Move up
                        moveUp = true;
                        yVelocity = random(1,3);
                    }
                }
            }
        }


        void update()  {
            // Conducts unit movement
            if (posX > -6) {
                moveX();
                moveY();
            } else {
                isLive = false;
            }
        }


        bool damage() {
            // Takes damage from player shot, returns true if killed
            bool killed = false;
            hp--;
            if(hp < 1) {
                isLive = false;
                killed = true;
            }
            return killed;
        }


        void draw() {
            // Draws live elite
            if(isLive) {
                sprites.drawExternalMask(posX,posY,eliteSprites,eliteMasks,type,type);
            }
        }


        int checkXPos() {
            // Returns x-position
            return posX;
        }


        int checkYPos() {
            // Returns y-position
            return posY;
        }


        bool checkLife() {
            // Returns current alive status
            return isLive;
        }


        void killMe() {
            // Sets enemy as dead
            isLive = false;
        }
};




class Phos {
    // Player ship
    private:
        int posX = 0; int posY = 32;
        int velocity = 2; // Speed of vertical movement
        int lives  = 0; // Number of remaining ships
        bool active = true; // If ship is currently alive


    public:
        void setGameVars(int maxLives) {
            // Sets variables for a new game
            active = true;
            posY = 32;
            lives = maxLives;
        }


        void moveUp(int minY) {
            // Move Phos Upward
            if (posY > minY) {
                posY -= velocity;
            }
        }


        void moveDown(int maxY) {
            // Move Phos Downward
            if (posY < maxY) {
                posY += velocity;
            }
        }


        bool isHitEnemy(Enemy enemy)  {
            // Checks collision against one regular enemy
            bool isHit = false;
            if(active && enemy.checkXPos() <= 4) {
                if(enemy.checkYPos() > posY-7 && enemy.checkYPos() < posY+4)  {
                    active = false;
                    isHit =  true;
                }
            }
            return isHit;
        }


        bool isHitElite(Elite elite) {
            // Checks collision against elite enemy
            bool isHit = false;
            if(active && elite.checkXPos() <= 2) {
                if(elite.checkYPos() > posY-7 && elite.checkYPos() < posY+8)  {
                    active = false;
                    isHit = true;
                }
            }
            return isHit;
        }


        void draw() {
            // Draw player ship
            if(active) {
                sprites.drawExternalMask(posX,posY,phosSprite,phosMask,0,0);
            }
        }


        int checkYPos() {
            // Returns current y-position
            return posY;
        }


        int checkLives() {
            // Returns current ship count
            return lives;
        }


        bool isAlive() {
            // Returns current ship life status
            return active;
        }


        void newLife() {
            // Uses a life to continue play
            lives -= 1;
            if(lives > 0) {
                posY = 32;
                active = true;
            }
        }


        void addLife() {
            // Adds earned life
            lives += 1;
        }
};




class Shot {
    // Bullet objects
    private:
        int posX; int posY; // Front position
        int velocity = 3; // Travel velocity
        int trail = 3; // Pixel length of drawn trail
        bool isLive = false; // Life of bullet
        int tailPos = 0;


    public:
        void shoot(int phosPosY, bool phosAlive) {
            // Shoots from Phos' current position
            if(phosAlive) {
                posY = phosPosY + 4;
                posX = 3;
                isLive = true;
                tailPos = random(3);
                shootSound();
            }

        }


        void updatePos()  {
            // Advance shot until end of screen
            if(isLive) {
                if (posX < 127) {
                    posX += velocity;
                } else {
                    isLive = false;
                }
            }
        }


        int hitEnemy(Enemy enemyArray[], int maxShips)  {
            // Loops all enemys to check for collision, returns point value
            int points = 0;
            for (int i = 0; i < maxShips; i++) {
                if (enemyArray[i].checkLife())  { // Only check live enemies

                    // Init dimensions
                    int yMin = enemyArray[i].checkYPos() + 3;
                    int yMax = enemyArray[i].checkYPos() + 9;
                    int xMin = enemyArray[i].checkXPos();
                    int xMax = enemyArray[i].checkXPos() + 5;

                    // Check position
                    if ((posY >=  yMin && posY <= yMax) && (posX >= xMin && posX <= xMax))  {
                        enemyArray[i].killMe();
                        isLive = false;
                        points = 10 * enemyArray[i].checkVel();
                        break;
                    }
                }
            }
            return points;
        }


        bool hitElite(Elite elite) {
            // Check hit with elite enemy, reduces hp, returns point value on kill
            bool hit = false;
            if(elite.checkLife()) { // Only check if live

                // Init dimensions
                int yMin = elite.checkYPos();
                int yMax = elite.checkYPos() + 9;
                int xMin = elite.checkXPos();
                int xMax = elite.checkXPos() + 7;

                // Check position
                if ((posY >=  yMin && posY <= yMax) && (posX >= xMin && posX <= xMax))  {
                    isLive = false;
                    hit = true;
                }
            }
            return hit;
        }


        void draw(int gameState) {
            // Draws live shots
            if(isLive) {
                if(gameState == 1) {
                    switch(tailPos) {
                        case 0:
                            arduboy.drawLine(posX, posY-1, posX - (trail+2), posY-1);
                            arduboy.drawLine(posX, posY, posX - trail, posY);
                            tailPos = 1;
                            break;
                        case 1:
                            arduboy.drawLine(posX, posY-1, posX - (trail+1), posY-1);
                            arduboy.drawLine(posX, posY, posX - trail, posY);
                            tailPos = 2;
                            break;
                        case 2:
                            arduboy.drawLine(posX, posY-1, posX - trail, posY-1);
                            arduboy.drawLine(posX, posY, posX - (trail+2), posY);
                            tailPos = 3;
                            break;
                        case 3:
                            arduboy.drawLine(posX, posY-1, posX - trail, posY-1);
                            arduboy.drawLine(posX, posY, posX - (trail+1), posY);
                            tailPos = 0;
                            break;
                    }
                } else {
                    arduboy.fillRect(posX-5,posY-1,5,2);
                }
            }
        }


        bool checkLife() {
            // Returns if shot is active
            return isLive;
        }


        void killMe() {
            // Kills shot
            isLive = false;
        }
};


#endif
