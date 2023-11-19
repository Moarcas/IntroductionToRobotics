#include <EEPROM.h> 
#include "menu.h"
#include "input_utils.h"
#include "led.h"
#include "ldr_sensor.h"
#include "ultrasonic_sensor.h"

int selectedOption;

bool anotherReadingInProcess = false;

bool currentAlertState = false;

MenuState currentMenuState = MAIN_MENU;

void setup() {
    Serial.begin(9600); 

    setupIR();
    setupLed();
    setupLdrSensor();
    setupUltrasonicSensor();

    Serial.println(F("Welcome Back!"));
    showMainMenu(); 
}

void loop() {

    ldrSensorProcessing();
    ultrasonicSensorProcessing();

    currentAlertState = ldrSensorAlert() || ultrasonicSensorAlert();

    ledChangeAlertMode(currentAlertState); 

    if (anotherReadingInProcess == false && (selectedOption = getInput()) == -1) 
        return;

    currentMenuState = getNextMenuState(selectedOption); // can be a menu or an action

    processMenuStateTransition(currentMenuState); // show a menu or execute an action
}
