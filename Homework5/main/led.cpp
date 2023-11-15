#include "led.h"
#include "Arduino.h"
#include <EEPROM.h>

const int pinRed = 9;
const int pinGreen = 10;
const int pinBlue = 11;

const int automaticModeAddressMemory = 8;
const int redMemoryAddress = 10;
const int greenMemoryAddress = 12;
const int blueMemoryAddress = 14;

void setupLed() {
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);
}

void updateColors(int redIntensity, int greenIntensity, int blueIntensity) {
    EEPROM.put(redMemoryAddress, redIntensity);
    EEPROM.put(greenMemoryAddress, greenIntensity);
    EEPROM.put(blueMemoryAddress, blueIntensity);
}

void changeAutomaticMode(bool value) {
    EEPROM.put(automaticModeAddressMemory, value);
}

bool getAutomaticMode() {
    bool automaticMode;
    EEPROM.get(automaticModeAddressMemory, automaticMode);
    return automaticMode;
}

void changeColor(int redValue = 0, int greenValue = 0, int blueValue = 0) {
    analogWrite(pinRed, redValue);
    analogWrite(pinGreen, greenValue);
    analogWrite(pinBlue, blueValue);
}

void ledTurnAlertModeOn() {
    if (getAutomaticMode() == true) {
        changeColor(255, 0, 0);
    } else {
        int redIntensity, greenIntensity, blueIntensity;
        EEPROM.get(redMemoryAddress, redIntensity);
        EEPROM.get(greenMemoryAddress, greenIntensity);
        EEPROM.get(blueMemoryAddress, blueIntensity);
        changeColor(redIntensity, greenIntensity, blueIntensity); 
    }
}

void ledChangeAlertMode(bool alertMode) {
    if (!alertMode) 
        changeColor(0, 10, 0);
    else 
        ledTurnAlertModeOn();
}
