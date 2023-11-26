#ifndef PLAYER.H
#define PLAYER.H
#include "matrix.h"

void generatePlayerPosition(int matrix[matrixSize][matrixSize]);

void showPlayer(int matrix[matrixSize][matrixSize]);

void movePlayer(int matrix[matrixSize][matrixSize], char direction);

Position getPlayerPosition();

char getPlayerOrientation();

#endif
