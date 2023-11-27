#ifndef PLAYER.H
#define PLAYER.H
#include "map.h"

void generatePlayerPosition(int gameMap[mapSize][mapSize]);

void showPlayer(int gameMap[mapSize][mapSize]);

void movePlayer(int gameMap[mapSize][mapSize], char direction);

Position getPlayerPosition();

char getPlayerOrientation();

#endif
