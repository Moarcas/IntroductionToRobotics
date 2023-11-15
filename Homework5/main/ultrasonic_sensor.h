#ifndef ULTRASONIC_SENSOR.H
#define ULTRASONIC_SENSOR.H
#include "Arduino.h"

void setupUltrasonicSensor();

int ultrasonicSensorGetValue();

void ultrasonicSensorChangeThreshold(int);

void ultrasonicSensorChangeSamplingInterval(int);

int ultrasonicSensorGetThreshold();

int ultrasonicSensorGetSamplingInterval();

bool ultrasonicSensorAlert();

bool ultrasonicSensorReadyToStart();

#endif
