#pragma once
#include "segmentDisplay.h">
#include "button.h"

void setup() {
    // Initialize the shift register pins and the display control pins
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    // Initialize digit control pins and set them to off
    for (int i = 0; i < displayCount; i++) {
        pinMode(displayDigits[i], OUTPUT);
        digitalWrite(displayDigits[i], LOW);
    }
    pinMode(startButtonPin, INPUT_PULLUP);
    Serial.begin(9600); // Start serial communication (not used in this program)
}

void loop() {
  // Sequentially display all encodings on the 7-segment display
  for (int i = 0; i < encodingsNumber; i++) {
    writeReg(encodingArray[i]); // Write the encoding to the shift register
    //writeReg(encodingArray[i]); // Write the encoding to the shift register
    delay(800); // Wait 400 milliseconds before displaying the next character
  }
}
