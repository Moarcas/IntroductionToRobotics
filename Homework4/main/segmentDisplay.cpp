#pragma once
#include "Arduino.h"
#include "segmentDisplay.h"

void writeReg(const int encoding[]) {
  // Send each bit of the encoding to the shift register
  digitalWrite(latchPin, LOW); // Prepare to send data
  for (int i = 0; i < regSize; i++) {
    digitalWrite(clockPin, LOW); // Set the clock pin low before sending data
    digitalWrite(dataPin, encoding[i]); // Send the data bit
    digitalWrite(clockPin, HIGH); // Clock the data bit into the register
  }
  digitalWrite(latchPin, HIGH); // Latch the data into the register to update the display
}
