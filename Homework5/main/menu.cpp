#include "menu.h"
#include "Arduino.h"
#include "input_utils.h"

String inputString = "";

void showMainMenu() {
  Serial.println("Main Menu");
  Serial.println("1. Sensor Settings");
  Serial.println("2. Reset Logged Data");
  Serial.println("3. System Status");
  Serial.println("4. RGB LED Control");
}

void showSensorSettingsMenu() {
    Serial.println("    Sensor Settings Menu");
    Serial.println("    1. Ultrasonic Sensor Sampling Interval");
    Serial.println("    2. Ultrasonic Sensor Alert Threshold");
    Serial.println("    3. LDR Sampling Interval");
    Serial.println("    4. LDR Alert Threshold");
    Serial.println("    5. Back");
}

void showResetLoggedDataMenu() {
    Serial.println("    Reset Logged Data Menu");
    Serial.println("    1. Ultrasonic Reset");
    Serial.println("    2. LDR Reset");
    Serial.println("    3. Back");
}

void showSystemStatusMenu() {
    Serial.println("    System Status Menu");
    Serial.println("    1. Current Sensor Readings");
    Serial.println("    2. Display Logged Data");
    Serial.println("    3. System Health");
    Serial.println("    4. Back");
}

void showRgbLedControlMenu() {
    Serial.println("    RGB LED Control Menu");
    Serial.println("    1. Set Red Value");
    Serial.println("    2. Set Green Value");
    Serial.println("    3. Set Blue Value");
    Serial.println("    4. Back");
}

MenuState nextStateFromMainMenu(int option) {
    MenuState nextState = MAIN_MENU;
    switch (option) {
        case 1:
            nextState = SENSOR_SETTINGS;
            break;
        case 2:
            nextState = RESET_LOGGED_DATA;
            break;
        case 3:
            nextState = SYSTEM_STATUS;
            break;
        case 4:
            nextState = RGB_LED_CONTROL;
            break;
        default:    
            showInputException();
            break;
    }
    return nextState;
}

MenuState nextStateFromSensorSettingsMenu(int option) {
    MenuState nextState = SENSOR_SETTINGS;
    switch (option) {
        case 1:
            nextState = ULTRASONIC_SENSOR_SAMPLING_INTERVAL;
            break;
        case 2:
            nextState = ULTRASONIC_SENSOR_ALERT_THRESHOLD;
            break;
        case 3:
            nextState = LDR_SAMPLING_INTERVAL;
            break;
        case 4:
            nextState = LDR_ALERT_THRESHOLD;
            break;
        case 5:
            nextState = MAIN_MENU;
            break;
        default:
            showInputException();
            break;
    }
    return nextState;
}

MenuState nextStateFromResetLoggedData(int option) {
    MenuState nextState = RESET_LOGGED_DATA;
    switch (option) {
        case 1:
            nextState = ULTRASONIC_RESET;
            break;
        case 2:
            nextState = LDR_RESET;
            break;
        case 3:
            nextState = MAIN_MENU;
            break;
        default:
            showInputException();
            break;
    }
    return nextState;
}

MenuState nextStateFromSystemStatus(int option) {
    MenuState nextState = SYSTEM_STATUS;
    switch (option) {
        case 1:
            nextState = CURRENT_SENSOR_READINGS;
            break;
        case 2:
            nextState = DISPLAY_LOGGED_DATA;
            break;
        case 3:
            nextState = SYSTEM_HEALTH;
            break;
        case 4:
            nextState = MAIN_MENU;
            break;
        default:
            showInputException();
            break;
    }
    return nextState;
}

MenuState nextStateFromRgbLedControl(int option) {
    MenuState nextState = RESET_LOGGED_DATA;
    switch (option) {
        case 1:
            nextState = SET_RED_VALUE;
            break;
        case 2:
            nextState = SET_GREEN_VALUE;
            break;
        case 3:
            nextState = SET_BLUE_VALUE;
            break;
        case 4:
            nextState = MAIN_MENU;
            break;
        default:
            showInputException();
            break;
    }
    return nextState;
}

void successfulRateChangeMessage(int rate) {
    Serial.print("      Sampling interval was changed to ");
    Serial.println(rate);
}

void successfulThresholdChangeMessage(int threshold) {
    Serial.print("      Threshold was changed to ");
    Serial.println(threshold);
}

int changeSensorSamplingInterval(MenuState currentMenuState) {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println("    Enter a value between 1 and 10"); 
    }

    int sensorRate = getInput(&inputString, 1, 10);

    if (sensorRate != -1) {
        if (currentMenuState == ULTRASONIC_SENSOR_SAMPLING_INTERVAL) {
            // TODO
        }
        if (currentMenuState == LDR_SAMPLING_INTERVAL) {
            // TODO
        }
        successfulRateChangeMessage(sensorRate);
        anotherReadingInProcess = false;
        return 1;
    }
    return 0;
}

int changeAlertThreshold(MenuState currentMenuState) {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println("    Enter a value between 1 and 100");
    }

    int newThreshold = getInput(&inputString, 1, 100);

    if (newThreshold != -1) {
        if (currentMenuState == ULTRASONIC_SENSOR_SAMPLING_INTERVAL) {
            // TODO
        }
        if (currentMenuState == LDR_SAMPLING_INTERVAL) {
            // TODO
        }
        successfulThresholdChangeMessage(newThreshold);
        anotherReadingInProcess = false;
        return 1;
    }
    return 0;
}
