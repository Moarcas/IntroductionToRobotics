#ifndef LDR_SENSOR.H
#define LDR_SENSOR.H
#include "Arduino.h"

void setupLdrSensor();

void ldrSensorProcessing();

void ldrSensorChangeThreshold(int);

void ldrSensorChangeSamplingInterval(int);

int ldrSensorGetThreshold();

int ldrSensorGetSamplingInterval();

int ldrSensorGetValue();

bool ldrSensorAlert();

void ldrSensorShowOutput(bool show);

#endif
