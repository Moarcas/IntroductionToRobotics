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
            DISPLAY_LOGGED_DATA,
            SYSTEM_HEALTH,
        RGB_LED_CONTROL,
            SET_RED_VALUE,
            SET_GREEN_VALUE,
            SET_BLUE_VALUE,
};

extern MenuState currentMenuState;

void showMainMenu();
void showSensorSettingsMenu();
void showResetLoggedDataMenu();
void showSystemStatusMenu();
void showRgbLedControlMenu();

int changeSensorSamplingInterval(MenuState currentMenuState);
int changeAlertThreshold(MenuState currentMenuState);

MenuState nextStateFromMainMenu(int option);
MenuState nextStateFromSensorSettingsMenu(int option);
MenuState nextStateFromResetLoggedData(int option);
MenuState nextStateFromSystemStatus(int option);
MenuState nextStateFromRgbLedControl(int option);

#endif
