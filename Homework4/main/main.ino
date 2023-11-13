#include "segmentDisplay.h"
#include "button.h"

int number = 0;
int savedLaps[4];
int currentLap = 0;
int indexLap = 0;
unsigned long lastIncrement = 0;
const int incrementPeriod = 100;
bool pauseMode = true;
bool lapViewMode = false;

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
    pauseMode = !pauseMode;
    if (lapViewMode) {
        number = 0;
        lapViewMode = false;
    }
}

void handleResetButton() {
    if (lapViewMode) {
        currentLap = 0;
        indexLap = 0;
        for (int i = 0; i < 4; i++)
            savedLaps[i] = 0;
    }

    if (pauseMode) {
        number = 0;
        lapViewMode = true;
    } 
}

void handleSaveButton() {
    if (!pauseMode) {
        savedLaps[currentLap % 4] = number;
        currentLap++;
    }

    if (lapViewMode && currentLap != 0) {
        number = savedLaps[indexLap % min(4, currentLap)];
        indexLap++;
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
        handleSaveButton();
    }

    if (pauseMode == false) {
        count();
    }

    writeNumberToDisplay(number);

}
