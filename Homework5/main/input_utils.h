#ifndef INPUT_UTILS.H
#define INPUT_UTILS .H
#include "Arduino.h"

void setupIR();

void showInputException();

int getInput(int minValue = 0, int maxValue = 1000);

extern bool anotherReadingInProcess;

void toggleInputMode(bool infraredMode);

#endif
