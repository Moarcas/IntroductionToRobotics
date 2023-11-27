#include "bullet.h"
#include "Arduino.h"

const int blinkDelay = 30;
static unsigned long lastBlink;

const int moveDelay = 150;
unsigned long lastMove;

Position bulletPosition;

char direction = 'n';

void changeBulletPosition(int gameMap[mapSize][mapSize]) {
    gameMap[bulletPosition.line][bulletPosition.column] = 0;
    bulletPosition.line += 1 * (direction == 'd') -1 * (direction == 'u');
    bulletPosition.column += 1 * (direction == 'r') -1 * (direction == 'l');
    
    if (!isOnMap(bulletPosition)) {
        direction = 'n';
        return;
    }
    if (isWall(bulletPosition)) {
        gameMap[bulletPosition.line][bulletPosition.column] = 0;
        direction = 'n';
    }
}

void showBullet(int gameMap[mapSize][mapSize]) {
    if (direction == 'n')
        return;

    if (millis() - lastBlink > blinkDelay) {
        gameMap[bulletPosition.line][bulletPosition.column] = 1 - gameMap[bulletPosition.line][bulletPosition.column];
        lastBlink = millis();
    }
    
    if (millis() - lastMove > moveDelay) {
        changeBulletPosition(gameMap);
        lastMove = millis();
    }
}

void shoot(Position playerPosition, char playerOrientation) {
    if (direction == 'n') {
        bulletPosition = playerPosition;
        direction = playerOrientation;
    }
}

