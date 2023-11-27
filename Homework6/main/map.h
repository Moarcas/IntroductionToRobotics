#ifndef MAP.H
#define MAP.H

struct Position {
    int line;
    int column;
};

const int matrixSize = 8;
const int mapSize = 16;

extern int gameMap[mapSize][mapSize];

void setupMatrix();

void generateMap(int gameMap[mapSize][mapSize]);

void showMap(int gameMap[mapSize][mapSize]);

bool isOnMap(Position);

bool isWall(Position);

void changeMiniMapPosition(Position playerPosition, char direction);

#endif
