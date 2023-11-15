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
    Serial.println("    2. Current Sensor Settings");
    Serial.println("    3. Back");
}

void showRgbLedControlMenu() {
    Serial.println("    RGB LED Control Menu");
    Serial.println("    1. Set Automatic Mode ON/OFF");
    Serial.println("    2. Color Control");
    Serial.println("    3. Back");
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
            nextState = CURRENT_SENSOR_SETTINGS;
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

void successfulRateChangeMessage(int rate) {
    Serial.print("      ->Sampling interval was changed to ");
    Serial.println(rate);
}

void successfulThresholdChangeMessage(int threshold) {
    Serial.print("      ->Threshold was changed to ");
    Serial.println(threshold);
}

void successfulResetMessage() {
    Serial.println("    ->The sensor has been successfully reset");
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

int resetSensor(MenuState currentMenuState) {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println("    Are you sure?");
        Serial.println("    1. Yes");
        Serial.println("    2. No");
    }

    int option = getInput(&inputString, 1, 2);

    if (option == 2) {
        anotherReadingInProcess = false;
        return 1;
    }

    if (option == 1) {
        if (currentMenuState == ULTRASONIC_RESET) {
            // TODO
        }
        if (currentMenuState == LDR_RESET) {
            // TODO
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
        Serial.println("    Showing Sensor Readings");
        Serial.println("    Press 0 to quit.");
        // TODO
        // - get samping rate
        // - save start time
    }

    //printSensorReading();
   
    if (getInput(&inputString, 0, 0) != -1) { // exit when 1 is pressed
        anotherReadingInProcess = false;
        return 1;
    } 
    return 0;
}

void showCurrentSensorSettings() {
    Serial.print("    Ultrasonic sampling rate: ");
    Serial.println();   //TODO
    Serial.print("    Ultrasonic threshold: ");
    Serial.println();   //TODO
    Serial.print("    LDR sampling rate: ");
    Serial.println();
    Serial.print("    LDR threshold: ");
    Serial.println();

}

int changeLedColors() {
    static bool redIsSet = false;
    static bool greenIsSet = false;
    static bool blueIsSet = false;
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        redIsSet = false;
        greenIsSet = false;
        blueIsSet = false;
        Serial.println("    Each value must be between 0 and 255!");
        Serial.println("    Enter red color value");
    }

    if (getInput(&inputString, 0, 255) != -1) {
        if (!redIsSet) {
            redIsSet = true;
            // TODO set value for red
            Serial.println("    ->The red color value has been successfully set");
            Serial.println("    Enter green color value");
            return 0;
        }
        if (!greenIsSet) {
            greenIsSet = true;
            // TODO set green color
            Serial.println("    ->The green color value has been successfully set");
            Serial.println("    Enter blue color value");
            return 0;
        }
        blueIsSet = true;
        // TODO set blue color
        Serial.println("    ->The blue color value has been successfully set");
        anotherReadingInProcess = false;
        return 1;
    }
    return 0;
}

int toggleLedAutomaticMode() {
    if (!anotherReadingInProcess) {
        anotherReadingInProcess = true;
        Serial.println("    Select Automatic Mode");
        Serial.println("    1. ON");
        Serial.println("    2. OFF");
    }

    int option = getInput(&inputString, 1, 2);

    if (option == -1)
        return 0;

    if (option == 1) {
        // TODO: turn on automatic mode
        Serial.println("    -> Automatic mode has been set ON successfully");
    } else {
        // TODO: turn off automatic mode
        Serial.println("    -> Automatic mode has been set OFF successfully");
    }
    anotherReadingInProcess = false;
    return 1;
}
