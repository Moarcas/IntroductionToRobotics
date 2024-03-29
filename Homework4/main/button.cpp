#include "button.h"
#include "Arduino.h"

int lastButtonValueRead[nrButtons];
int buttonState[nrButtons];
unsigned long timeLastChangeButton[nrButtons];

bool buttonIsPressed(const int buttonNumber) {
    bool isPressed = false;
    int buttonValueRead = !digitalRead(buttonPin[buttonNumber]);

    if (buttonValueRead != lastButtonValueRead[buttonNumber]) {
        timeLastChangeButton[buttonNumber] = millis();
    }
    if (millis() - timeLastChangeButton[buttonNumber] > debounceDelay && buttonValueRead != buttonState[buttonNumber]) {
        buttonState[buttonNumber] = buttonValueRead;
        isPressed = bool(buttonState[buttonNumber]);
    }
    lastButtonValueRead[buttonNumber] = buttonValueRead;
    return isPressed;
}

bool buttonIsPressedLong(const int buttonNumber) {
    bool isPressed = false;
    int buttonValueRead = !digitalRead(buttonPin[buttonNumber]);

    if (buttonValueRead != lastButtonValueRead[buttonNumber]) {
        timeLastChangeButton[buttonNumber] = millis();
    }
    if (millis() - timeLastChangeButton[buttonNumber] > longPressPeriod && buttonValueRead == 1) {
        timeLastChangeButton[buttonNumber] = millis();
        buttonState[buttonNumber] = 1;
        isPressed = 1;
    }
    lastButtonValueRead[buttonNumber] = buttonValueRead;
    return isPressed;
}
