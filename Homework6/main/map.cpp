#include "LedControl.h" // need the library
#include "map.h"
#include "player.h"
#include "bullet.h"

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);
const int matrixBrightness = 1;
const int wallProbability = 30;
Position miniMapPosition;

void setupMatrix() {
    lc.shutdown(0, false);
    lc.setIntensity(0, matrixBrightness);
    lc.clearDisplay(0);
}

void generateMap(int gameMap[mapSize][mapSize]) {
    int randomNumber;
    for (int i = 0; i < mapSize; i++)
        for (int j = 0; j < mapSize; j++) {
            randomNumber = random(100);
            gameMap[i][j] = int(randomNumber < wallProbability);
        }
}

void showMap(int gameMap[mapSize][mapSize]) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            lc.setLed(0, i, j, gameMap[miniMapPosition.line + i][miniMapPosition.column + j]);
        }
    }
    showPlayer(gameMap);
    showBullet(gameMap);
}

bool isOnMap(Position position) {
    return position.line >= 0 && position.line < mapSize && position.column >= 0 && position.column < mapSize;
}

bool isWall(Position position) {
    return gameMap[position.line][position.column];
}

void changeMiniMapPosition(Position playerPosition, char direction) {
    bool canMoveLeft = (direction == 'l' && miniMapPosition.column && playerPosition.column - miniMapPosition.column < 2);
    bool canMoveUp = (direction == 'u' && miniMapPosition.line && playerPosition.line - miniMapPosition.line < 2);
    bool canMoveRight = (direction == 'r' && miniMapPosition.column + matrixSize != mapSize && miniMapPosition.column + matrixSize - playerPosition.column < 3);
    bool canMoveDown = (direction == 'd' && miniMapPosition.line + matrixSize != mapSize && miniMapPosition.line + matrixSize - playerPosition.line < 3);


    if (canMoveLeft) {
        miniMapPosition.column--;
        return;
    }
    if (canMoveUp) {
        miniMapPosition.line--;
        return;
    }
    if (canMoveRight) {
        miniMapPosition.column++;
        return;
    }
    if (canMoveDown) {
        miniMapPosition.line++;
        return;
    }
}
