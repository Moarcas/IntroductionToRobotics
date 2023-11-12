#ifndef BUTTON.H
#define BUTTON.H

const int nrButtons = 3;

const int start = 0;
const int reset = 1;
const int save = 2;

const int buttonPin[nrButtons] = {8, 3, 2};

const int debounceDelay = 50;

extern int lastButtonValueRead[nrButtons];

extern int buttonState[nrButtons];

extern unsigned long timeLastChangeButton[nrButtons];

bool buttonIsPressed(const int pin);

#endif
