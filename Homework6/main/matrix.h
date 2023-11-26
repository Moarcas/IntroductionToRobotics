#ifndef MATRIX.H
#define MATRIX.H

struct Position {
    int line;
    int column;
};

const int matrixSize = 8;

extern int matrix[matrixSize][matrixSize];

void setupMatrix();

void generateMatrix(int matrix[matrixSize][matrixSize]);

void showMatrix(int matrix[matrixSize][matrixSize]);

bool isOnMatrix(Position);

bool isWall(Position);

#endif
