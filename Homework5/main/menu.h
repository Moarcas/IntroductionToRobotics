#ifndef MENU.H
#define MENU.H

#include "Arduino.h"

enum MenuState {
    MAIN_MENU,                                      
        SENSOR_SETTINGS,                            
            ULTRASONIC_SENSOR_SAMPLING_INTERVAL,
            ULTRASONIC_SENSOR_ALERT_THRESHOLD,
            LDR_SAMPLING_INTERVAL, 
            LDR_ALERT_THRESHOLD,
        RESET_LOGGED_DATA,
            ULTRASONIC_RESET,
            LDR_RESET,
        SYSTEM_STATUS,
            CURRENT_SENSOR_READINGS,
            CURRENT_SENSOR_SETTINGS,
            DISPLAY_LOGGED_DATA,
        RGB_LED_CONTROL,
            AUTOMATIC_MODE,
            COLOR_CONTROL,
        IR_CONTROL

};

extern MenuState currentMenuState;

void showMainMenu();
void showSensorSettingsMenu();
void showResetLoggedDataMenu();
void showSystemStatusMenu();
void showRgbLedControlMenu();

void processMenuStateTransition(MenuState& currentMenuState);

MenuState nextStateFromMainMenu(int option);
MenuState nextStateFromSensorSettingsMenu(int option);
MenuState nextStateFromResetLoggedData(int option);
MenuState nextStateFromSystemStatus(int option);
MenuState nextStateFromRgbLedControl(int option);
MenuState getNextMenuState(int option);

int changeSensorSamplingInterval(MenuState currentMenuState);
int changeAlertThreshold(MenuState currentMenuState);
int resetSensor(MenuState currentMenuState);
int showCurrentSensorReadings();
int changeLedColors();
int toggleLedAutomaticMode();
void showCurrentSensorSettings();
void showLoggedData();
int changeIrControl();

#endif
