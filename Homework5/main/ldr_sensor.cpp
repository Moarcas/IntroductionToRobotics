#include "ldr_sensor.h"
#include "Arduino.h"
#include <EEPROM.h>

const int ldrSensorValueMemoryAddress = 30;
const int thresholdMemoryAddress = 16;
const int samplingIntervalMemoryAddress = 18;
const int ldrPin = A0;
static unsigned long lastTimeRead;
static bool showOutput = false;

void setupLdrSensor() {
    pinMode(ldrPin, INPUT);
}

int ldrSensorReadValue() {
    return analogRead(ldrPin);
}

void ldrSensorChangeThreshold(int newThreshold) {
    EEPROM.put(thresholdMemoryAddress, newThreshold); 
}

void ldrSensorChangeSamplingInterval(int newSamplingInterval) {
    EEPROM.put(samplingIntervalMemoryAddress, newSamplingInterval);
}

bool ldrSensorAlert() {
    return ldrSensorGetValue() > ldrSensorGetThreshold();
}

bool ldrSensorReadyToStart() {
    return (millis() - lastTimeRead) > (ldrSensorGetSamplingInterval() * 1000);
}

void ldrSensorProcessing() {
    if (ldrSensorReadyToStart()) {
        EEPROM.put(ldrSensorValueMemoryAddress, ldrSensorReadValue());
        
        if (showOutput) {
            Serial.print("      ->LDR Sensor Value: ");
            Serial.println(ldrSensorGetValue());
        }

        lastTimeRead = millis();
    }
}

int ldrSensorGetValue() {
    int ldrSensorValue;
    EEPROM.get(ldrSensorValueMemoryAddress, ldrSensorValue);
    return ldrSensorValue;
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

void ldrSensorShowOutput(bool show) {
    showOutput = show;
}
