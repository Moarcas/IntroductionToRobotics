#include "bullet.h"
#include "Arduino.h"

const int blinkDelay = 30;
static unsigned long lastBlink;

const int moveDelay = 150;
unsigned long lastMove;

Position bulletPosition;

char direction = 'n';

void changeBulletPosition(int matrix[matrixSize][matrixSize]) {
    matrix[bulletPosition.line][bulletPosition.column] = 0;
    bulletPosition.line += 1 * (direction == 'u') -1 * (direction == 'd');
    bulletPosition.column += 1 * (direction == 'r') -1 * (direction == 'l');
    
    if (!isOnMatrix(bulletPosition)) {
        direction = 'n';
        return;
    }
    if (isWall(bulletPosition)) {
        matrix[bulletPosition.line][bulletPosition.column] = 0;
        direction = 'n';
    }
}

void showBullet(int matrix[matrixSize][matrixSize]) {
    if (direction == 'n')
        return;

    if (millis() - lastBlink > blinkDelay) {
        matrix[bulletPosition.line][bulletPosition.column] = 1 - matrix[bulletPosition.line][bulletPosition.column];
        lastBlink = millis();
    }
    
    if (millis() - lastMove > moveDelay) {
        changeBulletPosition(matrix);
        lastMove = millis();
    }
}

void shoot(Position playerPosition, char playerOrientation) {
    if (direction == 'n') {
        bulletPosition = playerPosition;
        direction = playerOrientation;
    }
}

