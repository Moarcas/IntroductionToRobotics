#include "menu.h"
#include "Arduino.h"
#include "input_utils.h"
#include "ldr_sensor.h"
#include "ultrasonic_sensor.h"
#include "led.h"

void showMainMenu() {
  Serial.println(F("Main Menu"));
  Serial.println(F("1. Sensor Settings"));
  Serial.println(F("2. Reset Logged Data"));
  Serial.println(F("3. System Status"));
  Serial.println(F("4. RGB LED Control"));
  Serial.println(F("5. Infrared Control"));
}

void showSensorSettingsMenu() {
    Serial.println(F("    Sensor Settings Menu"));
    Serial.println(F("    1. Ultrasonic Sensor Sampling Interval"));
    Serial.println(F("    2. Ultrasonic Sensor Alert Threshold"));
    Serial.println(F("    3. LDR Sampling Interval"));
    Serial.println(F("    4. LDR Alert Threshold"));
    Serial.println(F("    5. Back"));
}

void showResetLoggedDataMenu() {
    Serial.println(F("    Reset Logged Data Menu"));
    Serial.println(F("    1. Ultrasonic Reset"));
    Serial.println(F("    2. LDR Reset"));
    Serial.println(F("    3. Back"));
}

void showSystemStatusMenu() {
    Serial.println(F("    System Status Menu"));
    Serial.println(F("    1. Current Sensor Readings"));
    Serial.println(F("    2. Current Sensor Settings"));
    Serial.println(F("    3. Display Logged Data"));
    Serial.println(F("    4. Back"));
}

void showRgbLedControlMenu() {
    Serial.println(F("    RGB LED Control Menu"));
    Serial.println(F("    1. Set Automatic Mode ON/OFF"));
    Serial.println(F("    2. Color Control"));
    Serial.println(F("    3. Back"));
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
        case 5: 
            nextState = IR_CONTROL;
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
            nextState = CURRENT_SENSOR_SETTINGS;
            break;
        case 3:
            nextState = DISPLAY_LOGGED_DATA;
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
            nextState = AUTOMATIC_MODE;
            break;
        case 2:
            nextState = COLOR_CONTROL;
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

MenuState getNextMenuState(int selectedOption) {
    int nextMenuState;
    switch (currentMenuState) {
        case MAIN_MENU:
            nextMenuState = nextStateFromMainMenu(selectedOption);
            break;
        case SENSOR_SETTINGS:
            nextMenuState = nextStateFromSensorSettingsMenu(selectedOption);
            break;
        case RESET_LOGGED_DATA:
            nextMenuState = nextStateFromResetLoggedData(selectedOption);
            break;
        case SYSTEM_STATUS:
            nextMenuState = nextStateFromSystemStatus(selectedOption);
            break;
        case RGB_LED_CONTROL:
            nextMenuState = nextStateFromRgbLedControl(selectedOption);
            break;
    }
    return nextMenuState;
} 

void processMenuStateTransition(MenuState& currentMenuState) {
    switch (currentMenuState) {
        case MAIN_MENU:
            showMainMenu(); 
            break;
        case SENSOR_SETTINGS:
            showSensorSettingsMenu();
            break;
        case RESET_LOGGED_DATA:
            showResetLoggedDataMenu();
            break;
        case SYSTEM_STATUS:
            showSystemStatusMenu();
            break;
        case RGB_LED_CONTROL:
            showRgbLedControlMenu();
            break;
        case IR_CONTROL:
            if (changeIrControl()) {
                showMainMenu();
                currentMenuState = MAIN_MENU;
            }
            break;
        case ULTRASONIC_SENSOR_SAMPLING_INTERVAL:
        case LDR_SAMPLING_INTERVAL:
            if (changeSensorSamplingInterval(currentMenuState)) {
                showSensorSettingsMenu();
                currentMenuState = SENSOR_SETTINGS;
            }
            break;
        case ULTRASONIC_SENSOR_ALERT_THRESHOLD:
        case LDR_ALERT_THRESHOLD:
            if (changeAlertThreshold(currentMenuState)) {
                showSensorSettingsMenu();
                currentMenuState = SENSOR_SETTINGS;
            }
            break;
        case ULTRASONIC_RESET:
        case LDR_RESET:
            if (resetSensor(currentMenuState)) {
                showResetLoggedDataMenu();
                currentMenuState = RESET_LOGGED_DATA;
            }
            break;
        case CURRENT_SENSOR_READINGS:
            if (showCurrentSensorReadings()) {
                showSystemStatusMenu();
                currentMenuState = SYSTEM_STATUS;
            }
            break;
        case CURRENT_SENSOR_SETTINGS:
            showCurrentSensorSettings();
            showSystemStatusMenu();
            currentMenuState = SYSTEM_STATUS;
            break;
        case DISPLAY_LOGGED_DATA:
            showLoggedData();
            showSystemStatusMenu();
            currentMenuState = SYSTEM_STATUS;
            break;
        case AUTOMATIC_MODE:
            if (toggleLedAutomaticMode()) {
                showRgbLedControlMenu();
                currentMenuState = RGB_LED_CONTROL;
            }
            break;
        case COLOR_CONTROL:
            if (changeLedColors()) {
                showRgbLedControlMenu();
                currentMenuState = RGB_LED_CONTROL;
            }
            break;
        default:
            Serial.println(F("Unexpected error"));
    }
}

void successfulRateChangeMessage(int rate) {
    Serial.print(F("      ->Sampling interval was changed to "));
    Serial.println(rate);
}

void successfulThresholdChangeMessage(int threshold) {
    Serial.print(F("      ->Threshold was changed to "));
    Serial.println(threshold);
}

void successfulResetMessage() {
    Serial.println(F("    ->The sensor has been successfully reset"));
}

int changeSensorSamplingInterval(MenuState currentMenuState) {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println(F("    Enter a value between 1 and 10")); 
    }

    int sensorRate = getInput(1, 10);

    if (sensorRate != -1) {
        if (currentMenuState == ULTRASONIC_SENSOR_SAMPLING_INTERVAL) {
            ultrasonicSensorChangeSamplingInterval(sensorRate);
        }
        if (currentMenuState == LDR_SAMPLING_INTERVAL) {
            ldrSensorChangeSamplingInterval(sensorRate);
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
        Serial.println(F("    Enter a value between 1 and 300"));
    }

    int newThreshold = getInput(1, 300);

    if (newThreshold != -1) {
        if (currentMenuState == ULTRASONIC_SENSOR_ALERT_THRESHOLD) {
            ultrasonicSensorChangeThreshold(newThreshold);
        }
        if (currentMenuState == LDR_ALERT_THRESHOLD) {
            ldrSensorChangeThreshold(newThreshold);
        }
        successfulThresholdChangeMessage(newThreshold);
        anotherReadingInProcess = false;
        return 1;
    }
    return 0;
}

int resetSensor(MenuState currentMenuState) {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println(F("    Are you sure?"));
        Serial.println(F("    1. Yes"));
        Serial.println(F("    2. No"));
    }

    int option = getInput(1, 2);

    if (option == 2) {
        anotherReadingInProcess = false;
        return 1;
    }

    if (option == 1) {
        if (currentMenuState == ULTRASONIC_RESET) {
            ultrasonicSensorReset();
        }
        if (currentMenuState == LDR_RESET) {
            ldrSensorReset();
        }
        successfulResetMessage();
        anotherReadingInProcess = false;
        return 1;
    }
    return 0;
};

int showCurrentSensorReadings() {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println(F("    Showing Sensor Readings"));
        Serial.println(F("    Press 0 to quit."));
        ldrSensorShowOutput(true);
        ultrasonicSensorShowOutput(true);
    }

    if (getInput(0, 0) != -1) { // exit when 0 is pressed
        anotherReadingInProcess = false;
        ldrSensorShowOutput(false);
        ultrasonicSensorShowOutput(false);
        return 1;
    } 
    return 0;
}

void showCurrentSensorSettings() {
    Serial.print(F("    Ultrasonic sampling rate: "));
    Serial.println(ultrasonicSensorGetSamplingInterval());
    Serial.print(F("    Ultrasonic threshold: "));
    Serial.println(ultrasonicSensorGetThreshold());
    Serial.print(F("    LDR sampling rate: "));
    Serial.println(ldrSensorGetSamplingInterval());
    Serial.print(F("    LDR threshold: "));
    Serial.println(ldrSensorGetThreshold());
}

void showLoggedData() {
    ultrasonicSensorShowLoggedData();
    ldrSensorShowLoggedData();
}

int changeLedColors() {
    int intensity;
    static int redIntensity = -1;
    static int greenIntensity = -1;
    static int blueIntensity = -1;
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        redIntensity = -1;
        greenIntensity = -1;
        blueIntensity = -1;
        Serial.println(F("    Each value must be between 0 and 255!"));
        Serial.println(F("    Enter red color value"));
    }

    if ((intensity = getInput(0, 255)) != -1) {
        if (redIntensity == -1) {
            redIntensity = intensity;
            Serial.println(F("    ->The red color value has been successfully set"));
            Serial.println(F("    Enter green color value"));
            return 0;
        }
        if (greenIntensity == -1) {
            greenIntensity = intensity;
            Serial.println(F("    ->The green color value has been successfully set"));
            Serial.println(F("    Enter blue color value"));
            return 0;
        }
        blueIntensity = intensity;
        updateColors(redIntensity, greenIntensity, blueIntensity);
        Serial.println(F("    ->The blue color value has been successfully set"));
        anotherReadingInProcess = false;
        return 1;
    }
    return 0;
}

int toggleLedAutomaticMode() {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println(F("    Select Automatic Mode"));
        Serial.println(F("    1. ON"));
        Serial.println(F("    2. OFF"));
    }

    int option = getInput(1, 2);

    if (option == -1)
        return 0;

    if (option == 1) {
        changeAutomaticMode(true);
        Serial.println(F("    -> Automatic mode has been set ON successfully"));
    } else {
        changeAutomaticMode(false);
        Serial.println(F("    -> Automatic mode has been set OFF successfully"));
    }
    anotherReadingInProcess = false;
    return 1;
}

int changeIrControl() {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println(F("    Select the desired input mode:"));
        Serial.println(F("    1. Keyboard"));
        Serial.println(F("    2. Infrared Remote"));
    }

    int option = getInput(1, 2);

    if (option == -1) 
        return 0;

    if (option == 1) {
        toggleInputMode(false); // infrearedMode = false
        Serial.println(F("    -> Switched to Keyboard input mode"));
    } else {
        toggleInputMode(true); // infaredMode = true
        Serial.println(F("    -> Switched to Infrared Remote input mode"));
    }
    anotherReadingInProcess = false;
    return 1;
}
