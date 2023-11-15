#include "input_utils.h"
#include "Arduino.h"

void showInputException() {
    Serial.println("Invalid option. Please try again");
}

int getInput(String* inputString, int minValue, int maxValue) {
    if (Serial.available() > 0) {
        char valueRead = char(Serial.read());  
        *inputString += valueRead;

        if (valueRead == '\n') {
            int number = atoi(inputString->c_str());
            *inputString = "";

            if (number >= minValue && number <= maxValue)
                return number;

            showInputException();
            return -1;
        }

        if (!isDigit(valueRead)) {
            *inputString = "";
            showInputException();
        }
    }
    return -1;

}
