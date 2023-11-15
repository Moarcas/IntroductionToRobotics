#include "ldr_sensor.h"
#include "Arduino.h"
#include <EEPROM.h>

const int thresholdMemoryAddress = 16;
const int samplingIntervalMemoryAddress = 18;
const int ldrPin = A0;
static unsigned long lastTimeStart;

void setupLdrSensor() {
    pinMode(ldrPin, INPUT);
}

int ldrSensorGetValue() {
    lastTimeStart = millis();
    return analogRead(ldrPin);
}

void ldrSensorChangeThreshold(int newThreshold) {
    EEPROM.put(thresholdMemoryAddress, newThreshold); 
}

void ldrSensorChangeSamplingInterval(int newSamplingInterval) {
    EEPROM.put(samplingIntervalMemoryAddress, newSamplingInterval);
}

int ldrSensorGetThreshold() {
    int threshold;
    EEPROM.get(thresholdMemoryAddress, threshold);
    return threshold;
}

int ldrSensorGetSamplingInterval() {
    int samplingInterval;
    EEPROM.get(samplingIntervalMemoryAddress, samplingInterval);
    return samplingInterval;
}

bool ldrSensorAlert() {
    return ldrSensorGetValue() > ldrSensorGetThreshold();
}

bool ldrSensorReadyToStart() {
    return (millis() - lastTimeStart) > (ldrSensorGetSamplingInterval() * 1000);
}

void ldrSensorPrintReading() {
    
}
