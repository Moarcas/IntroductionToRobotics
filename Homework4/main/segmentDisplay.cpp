#include "Arduino.h"
#include "segmentDisplay.h"

void writeReg(int digit, int writeDp) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, byteEncodings[digit] + writeDp);
    digitalWrite(latchPin, HIGH);
}

void changeDisplay(int indexDisplay) {
    for (int i = 0; i < displayCount; i++) {
        digitalWrite(displayDigits[i], 1);
    }
    digitalWrite(displayDigits[indexDisplay], 0);
}

void setDisplaysToZero(int currentDisplay) {
    while (currentDisplay--) {
        changeDisplay(currentDisplay);
        writeReg(0, (currentDisplay == 2));
        writeReg(emptyDisplay);
    }
}

void writeNumberToDisplay(int number) {
    int currentDisplay = displayCount - 1;
    while (number) {
        changeDisplay(currentDisplay--);
        writeReg(number % 10, (currentDisplay == 1));
        number /= 10; 
        writeReg(emptyDisplay);
    }
    setDisplaysToZero(currentDisplay + 1);
}

