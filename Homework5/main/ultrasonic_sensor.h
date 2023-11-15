#ifndef ULTRASONIC_SENSOR.H
#define ULTRASONIC_SENSOR.H
#include "Arduino.h"

void setupUltrasonicSensor();

void ultrasonicSensorProcessing();

void ultrasonicSensorChangeThreshold(int);

void ultrasonicSensorChangeSamplingInterval(int);

int ultrasonicSensorGetThreshold();

int ultrasonicSensorGetSamplingInterval();

int ultrasonicSensorGetValue();

bool ultrasonicSensorAlert();

#endif
