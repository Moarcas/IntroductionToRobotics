#include "ultrasonic_sensor.h"
#include "Arduino.h"
#include <EEPROM.h>

const int thresholdMemoryAddress = 20;
const int samplingIntervalMemoryAddress = 22;
const int ldrPin = A0;
const int trigPin = 6;
const int echoPin = 5;
static unsigned long lastTimeStart;

void setupUltrasonicSensor() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int ultrasonicSensorGetValue() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    lastTimeStart = millis();
    return pulseIn(echoPin, HIGH) * 0.034/2;
}

void ultrasonicSensorChangeThreshold(int newThreshold) {
    EEPROM.put(thresholdMemoryAddress, newThreshold); 
}

void ultrasonicSensorChangeSamplingInterval(int newSamplingInterval) {
    EEPROM.put(samplingIntervalMemoryAddress, newSamplingInterval);
}

int ultrasonicSensorGetThreshold() {
    int threshold;
    EEPROM.get(thresholdMemoryAddress, threshold);
    return threshold;
}

int ultrasonicSensorGetSamplingInterval() {
    int samplingInterval;
    EEPROM.get(samplingIntervalMemoryAddress, samplingInterval);
    return samplingInterval;
}

bool ultrasonicSensorAlert() {
    return ultrasonicSensorGetValue() > ultrasonicSensorGetThreshold();
}

bool ultrasonicSensorReadyToStart() {
    return (millis() - lastTimeStart) > (ultrasonicSensorGetSamplingInterval() * 1000);
}
