#ifndef INPUT_UTILS.H
#define INPUT_UTILS.H
#include "Arduino.h"

void showInputException();

int getInput(String* inputString, int minValue = 0, int maxValue = 1000);

extern bool anotherReadingInProcess;

#endif
