#ifndef LDR_SENSOR.H
#define LDR_SENSOR.H
#include "Arduino.h"

void setupLdrSensor();

int ldrSensorGetValue();

void ldrSensorChangeThreshold(int);

void ldrSensorChangeSamplingInterval(int);

int ldrSensorGetThreshold();

int ldrSensorGetSamplingInterval();

bool ldrSensorAlert();

bool ldrSensorReadyToStart();

#endif
