#include "matrix.h"
#include "Arduino.h"
#include "bullet.h"
#include "player.h"

Position playerPosition;

const int blinkDelay = 200;
static unsigned long lastBlink;

char playerOrientation = 'u';

void generatePlayerPosition(int matrix[][matrixSize]) {
    for (int i = 0; i < matrixSize; i++) 
        for (int j = 0; j < matrixSize; j++) 
            if (!matrix[i][j]) {
                playerPosition = (Position){i, j};
                return;
            }
}

void showPlayer(int matrix[][matrixSize]) {
    if (millis() - lastBlink > blinkDelay) {
        matrix[playerPosition.line][playerPosition.column] = 1 - matrix[playerPosition.line][playerPosition.column];
        lastBlink = millis();
    }
}


void movePlayer(int matrix[][matrixSize], char direction) {
    Position nextPlayerPosition = playerPosition;

    nextPlayerPosition.line += 1 * (direction == 'u') -1 * (direction == 'd');
    nextPlayerPosition.column += 1 * (direction == 'r') -1 * (direction == 'l');

    if (isOnMatrix(nextPlayerPosition) && !isWall(nextPlayerPosition)) {
        matrix[playerPosition.line][playerPosition.column] = 0;
        playerPosition = nextPlayerPosition;
    }
    playerOrientation = direction;
}

Position getPlayerPosition() {
    return playerPosition;
}

char getPlayerOrientation() {
    return playerOrientation;
}
