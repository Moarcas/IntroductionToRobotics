#include "Arduino.h"
#include "map.h"
#include "bullet.h"
#include "player.h"

Position playerPosition;

const int blinkDelay = 200;
static unsigned long lastBlink;

char playerOrientation = 'u';

void generatePlayerPosition(int gameMap[][mapSize]) {
    for (int i = 0; i < mapSize; i++) 
        for (int j = 0; j < mapSize; j++) 
            if (!gameMap[i][j]) {
                playerPosition = (Position){i, j};
                return;
            }
}

void showPlayer(int gameMap[][mapSize]) {
    if (millis() - lastBlink > blinkDelay) {
        gameMap[playerPosition.line][playerPosition.column] = 1 - gameMap[playerPosition.line][playerPosition.column];
        lastBlink = millis();
    }
}


void movePlayer(int gameMap[][mapSize], char direction) {
    Position nextPlayerPosition = playerPosition;

    nextPlayerPosition.line += 1 * (direction == 'd') -1 * (direction == 'u');
    nextPlayerPosition.column += 1 * (direction == 'r') -1 * (direction == 'l');

    if (isOnMap(nextPlayerPosition) && !isWall(nextPlayerPosition)) {
        gameMap[playerPosition.line][playerPosition.column] = 0;
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
