#include "map.h"
#include "player.h"
#include "joystick.h"
#include "bullet.h"

int gameMap[mapSize][mapSize];

void setup() {
    Serial.begin(9600);

    setupMatrix();
    setupJoystick();

    generateMap(gameMap);
    generatePlayerPosition(gameMap);

    delay(1000);
}

void loop() {
    showMap(gameMap);

    char direction = joystickMove();

    if (direction != 'n')
        movePlayer(gameMap, direction);
        changeMiniMapPosition(getPlayerPosition(), direction);

    if (buttonIsPressed())
        shoot(getPlayerPosition(), getPlayerOrientation());
}

