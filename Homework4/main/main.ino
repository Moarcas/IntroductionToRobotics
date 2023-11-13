#include "segmentDisplay.h"
#include "button.h"

const int pauseMode = 0;
const int countMode = 1;
const int lapViewMode = 2;

int number = 0;
int savedLaps[4];
int indexLastLap = 0;
int indexCurrentLap = 0;
unsigned long lastIncrement = 0;
const int incrementPeriod = 100;
int currentMode = pauseMode;

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
    pinMode(buttonPin[start], INPUT_PULLUP);
    pinMode(buttonPin[reset], INPUT_PULLUP);
    pinMode(buttonPin[save], INPUT_PULLUP);

    Serial.begin(9600); 
}

void count() {
    if (millis() - lastIncrement > incrementPeriod) {
        number = (number + 1) % 10000;
        lastIncrement = millis();
    }
}

void handleStartButton() {
    if (currentMode == lapViewMode) {
        number = 0;
    }
    currentMode = currentMode != countMode ? countMode : pauseMode;
}

void handleResetButton() {
    if (currentMode == lapViewMode) {
        indexLastLap = 0;
        indexCurrentLap = 0;
        for (int i = 0; i < 4; i++)
            savedLaps[i] = 0;
    }

    if (currentMode == pauseMode) {
        currentMode = lapViewMode;
    }

    number = 0;
}

void handleSaveButton(bool longPress) {
    if (currentMode == countMode && longPress == false) {
        savedLaps[indexLastLap % 4] = number;
        indexLastLap++;
    }
    if (currentMode == lapViewMode && indexLastLap != 0) {
       number = savedLaps[indexCurrentLap % min(4, indexLastLap)];
       indexCurrentLap++;
    }
}

void loop() {
    
    if (buttonIsPressed(start)) {
        handleStartButton();
    } 

    if (buttonIsPressed(reset)) {
        handleResetButton();
    }

    if (buttonIsPressed(save)) {
        handleSaveButton(false);
    }

    if (buttonIsPressedLong(save)) {
        handleSaveButton(true);
    }

    if (currentMode == countMode) {
        count();
    }

    writeNumberToDisplay(number);

}
