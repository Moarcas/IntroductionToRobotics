#include <EEPROM.h> 
#include "menu.h"
#include "input_utils.h"

int selectedOption;

bool anotherReadingInProcess = false;

String inputStringMenu = "";

MenuState currentMenuState = MAIN_MENU;

void setup() {
    Serial.begin(9600); 
    Serial.println("Welcome Back!");
    showMainMenu(); 
}

void loop() {

    if (anotherReadingInProcess == false && (selectedOption = getInput(&inputStringMenu)) == -1)  // Invalid input
        return;

    inputStringMenu = "";
    
    switch (currentMenuState) {
        case MAIN_MENU:
            currentMenuState = nextStateFromMainMenu(selectedOption);
            break;
        case SENSOR_SETTINGS:
            currentMenuState = nextStateFromSensorSettingsMenu(selectedOption);
            break;
        case RESET_LOGGED_DATA:
            currentMenuState = nextStateFromResetLoggedData(selectedOption);
            break;
        case SYSTEM_STATUS:
            currentMenuState = nextStateFromSystemStatus(selectedOption);
            break;
        case RGB_LED_CONTROL:
            currentMenuState = nextStateFromRgbLedControl(selectedOption);
            break;
    }

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
        case ULTRASONIC_SENSOR_SAMPLING_INTERVAL:
            if (changeSensorSamplingInterval(currentMenuState) == 1) {
                showSensorSettingsMenu();
                currentMenuState = SENSOR_SETTINGS;
            }
            break;
        case ULTRASONIC_SENSOR_ALERT_THRESHOLD:
            if (changeAlertThreshold(currentMenuState) == 1) {
                showSensorSettingsMenu();
                currentMenuState = SENSOR_SETTINGS;
            }
            break;
        case LDR_SAMPLING_INTERVAL:
            if (changeSensorSamplingInterval(currentMenuState) == 1) {
                showSensorSettingsMenu();
                currentMenuState = SENSOR_SETTINGS;
            }
            break;
        case LDR_ALERT_THRESHOLD:
            if (changeAlertThreshold(currentMenuState) == 1) {
                showSensorSettingsMenu();
                currentMenuState = SENSOR_SETTINGS;
            }
            break;
        default:
            Serial.println("Unexpected error");
    }
}
