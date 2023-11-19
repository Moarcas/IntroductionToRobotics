#include "input_utils.h"
#include "Arduino.h"
#include <DIYables_IRcontroller.h> // Library for IR Receiver
                        
#define IR_RECEIVER_PIN 7

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200); // debounce time is 200ms

bool infraredModeActive = false;

void setupIR() {
    irController.begin();
}

void showInputException() {
    Serial.println(F("Invalid option. Please try again"));
}

bool isValid(String inputString, int minValue, int maxValue) {
    for (int i = 0; i < inputString.length(); i++) {
        if (inputString[i] < '0' || inputString[i] > '9')
            return false;
    }
    int number = atoi(inputString.c_str());
    if (number < minValue || number > maxValue) 
        return false;
    return true;
}

int getInputFromIR(int minValue, int maxValue) {
    static int numberRead = 0;
    int digitRead = -1;
    Key21 key = irController.getKey();
    if (key != Key21::NONE) {
        switch (key) {
            case Key21::KEY_NEXT:
                if (numberRead >= minValue && numberRead <= maxValue) {
                    int copy = numberRead;
                    numberRead = 0;
                    return copy;
                }
                numberRead = 0;
                showInputException();
                break;

            case Key21::KEY_0:
                digitRead = 0;
                break;

            case Key21::KEY_1:
                digitRead = 1;
                break;

            case Key21::KEY_2:
                digitRead = 2;
                break;

            case Key21::KEY_3:
                digitRead = 3;
                break;

            case Key21::KEY_4:
                digitRead = 4;
                break;

            case Key21::KEY_5:
                digitRead = 5;
                break;

            case Key21::KEY_6:
                digitRead = 6;
                break;

            case Key21::KEY_7:
                digitRead = 7;
                break;

            case Key21::KEY_8:
                digitRead = 8;
                break;

            case Key21::KEY_9:
                digitRead = 9;
                break;

            default:
                numberRead = 0;
                showInputException();
                break;
        }
    }
    if (digitRead != -1) {
        numberRead = numberRead * 10 + digitRead;
    }

    return -1;
}

int getInputFromKeyboard(int minValue, int maxValue) {
    static String inputString = "";
    if (Serial.available() > 0) {
        char valueRead = char(Serial.read());  

        if (valueRead == '\n') {
            if (!isValid(inputString, minValue, maxValue)) {
                showInputException();
                inputString = "";
                return -1;
            }
            int number = atoi(inputString.c_str());
            inputString = "";
            return number;
        }
        inputString += valueRead;
    }
    return -1;
}

int getInput(int minValue, int maxValue) {
    if (infraredModeActive == false)
        return getInputFromKeyboard(minValue, maxValue);
    else
        return getInputFromIR(minValue, maxValue);
}

void toggleInputMode(bool infraredMode) {
    infraredModeActive = infraredMode;
}

