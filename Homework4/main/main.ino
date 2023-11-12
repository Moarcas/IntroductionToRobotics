#include "segmentDisplay.h"
#include "button.h"

int number = 0;
int savedLaps[4];
int currentLap = 0;
int indexLap = 0;
unsigned long lastIncrement = 0;
const int incrementPeriod = 100;
bool pauseMode = true;

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


void loop() {
    
    if (buttonIsPressed(start)) {
        pauseMode = !pauseMode;
    } 

    if (pauseMode == true && buttonIsPressed(reset)) {
        number = 0;
        lastIncrement = millis();
    }

    if (buttonIsPressed(save)) {
        if (pauseMode == false) {
            savedLaps[currentLap % 4] = number; 
            currentLap++;
        } else {
            number = savedLaps[indexLap % 4];
            indexLap++;
        }
    }

    if (pauseMode == false) {
        count();
    }

    writeNumberToDisplay(number);

}
