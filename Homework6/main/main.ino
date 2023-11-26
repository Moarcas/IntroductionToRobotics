#include "matrix.h"
#include "player.h"
#include "joystick.h"
#include "bullet.h"

int matrix[matrixSize][matrixSize];

void setup() {
    Serial.begin(9600);

    setupMatrix();
    setupJoystick();

    generateMatrix(matrix);
    generatePlayerPosition(matrix);

    delay(1000);
}

void loop() {
    showMatrix(matrix);

    char direction = joystickMove();

    if (direction != 'n')
        movePlayer(matrix, direction);

    if (buttonIsPressed())
        shoot(getPlayerPosition(), getPlayerOrientation());
}

