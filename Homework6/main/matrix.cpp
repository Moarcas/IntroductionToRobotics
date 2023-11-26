#include "LedControl.h" // need the library
#include "matrix.h"
#include "player.h"
#include "bullet.h"

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);
const int matrixBrightness = 1;
const int wallProbability = 30;

void setupMatrix() {
    lc.shutdown(0, false);
    lc.setIntensity(0, matrixBrightness);
    lc.clearDisplay(0);
}

void generateMatrix(int matrix[matrixSize][matrixSize]) {
    int randomNumber;
    for (int i = 0; i < matrixSize; i++)
        for (int j = 0; j < matrixSize; j++) {
            randomNumber = random(100);
            matrix[i][j] = int(randomNumber < wallProbability);
        }
}

void showMatrix(int matrix[matrixSize][matrixSize]) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            lc.setLed(0, i, j, matrix[i][j]);
        }
    }
    showPlayer(matrix);
    showBullet(matrix);
}

bool isOnMatrix(Position position) {
    return position.line >= 0 && position.line < matrixSize && position.column >= 0 && position.column < matrixSize;
} 

bool isWall(Position position) {
    return matrix[position.line][position.column];
}
