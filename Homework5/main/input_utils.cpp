#include "input_utils.h"
#include "Arduino.h"

void showInputException() {
    Serial.println("Invalid option. Please try again");
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

int getInput(String* inputString, int minValue, int maxValue) {
    if (Serial.available() > 0) {
        char valueRead = char(Serial.read());  

        if (valueRead == '\n') {
            if (!isValid(*inputString, minValue, maxValue)) {
                showInputException();
                *inputString = "";
                return -1;
            }
            int number = atoi(inputString->c_str());
            *inputString = "";
            return number;
        }
        *inputString += valueRead;
    }
    return -1;
}
