#include <EEPROM.h> 
#include "menu.h"
#include "input_utils.h"
#include "led.h"
#include "ldr_sensor.h"
#include "ultrasonic_sensor.h"

int selectedOption;

bool anotherReadingInProcess = false;

bool currentAlertMode = false;

MenuState currentMenuState = MAIN_MENU;

void setup() {
    Serial.begin(9600); 

    setupLed();
    setupLdrSensor();
    setupUltrasonicSensor();

    Serial.println("Welcome Back!");
    showMainMenu(); 
}

void loop() {

    currentAlertMode = ultrasonicSensorReadyToStart() && ultrasonicSensorAlert() ? true : currentAlertMode;
    currentAlertMode = ldrSensorReadyToStart() && ldrSensorAlert() ? true : currentAlertMode;

    ledChangeAlertMode(currentAlertMode); 

    if (anotherReadingInProcess == false && (selectedOption = getInput()) == -1) 
        return;

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
            Serial.println("Unexpected error");
    }
}
