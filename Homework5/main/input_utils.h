#ifndef INPUT_UTILS.H
#define INPUT_UTILS .H
#include "Arduino.h"

void showInputException();

int getInput(int minValue = 0, int maxValue = 1000);

void changeIrMode(bool infrared);

extern bool anotherReadingInProcess;

#endif
