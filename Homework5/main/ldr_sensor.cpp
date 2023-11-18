#include "ldr_sensor.h"
#include "Arduino.h"
#include <EEPROM.h>

const int ldrSensorNumberValuesSaved = 10;
const int ldrSensorFirstValueMemoryAddress = 150;
const int thresholdMemoryAddress = 16;
const int samplingIntervalMemoryAddress = 18;
const int ldrPin = A0;
const int intSize = 2;
static unsigned long lastTimeRead;
static bool showOutput = false;
static int indexValueToSave = 0;

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

void saveValueToMemory(int value) {
    int memoryAddress = ldrSensorFirstValueMemoryAddress + indexValueToSave * intSize;
    indexValueToSave++; 
    EEPROM.put(memoryAddress, value);
    if (indexValueToSave == ldrSensorNumberValuesSaved) 
        indexValueToSave = 0;
}

void ldrSensorProcessing() {
    if (ldrSensorReadyToStart()) {
        saveValueToMemory(ldrSensorReadValue());
        
        if (showOutput) {
            Serial.print("      ->LDR Sensor Value: ");
            Serial.println(ldrSensorGetValue());
        }

        lastTimeRead = millis();
    }
}

int ldrSensorGetValue() {
    int memoryAddress = ldrSensorFirstValueMemoryAddress + ((ldrSensorNumberValuesSaved + indexValueToSave - 1) % ldrSensorNumberValuesSaved) * intSize;
    int ldrSensorValue;
    EEPROM.get(memoryAddress, ldrSensorValue);
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

void ldrSensorShowLoggedData() {
    int memoryAddress;
    int ldrSensorValue;
    Serial.print("    ->Ldr Sensor Logged Data: ");
    for (int i = 1; i <= ldrSensorNumberValuesSaved; i++) {
        memoryAddress = ldrSensorFirstValueMemoryAddress + ((ldrSensorNumberValuesSaved - i + indexValueToSave) % ldrSensorNumberValuesSaved) * intSize;
        EEPROM.get(memoryAddress, ldrSensorValue);
        Serial.print(ldrSensorValue);
        Serial.print(" ");
    }
    Serial.println();
}

void ldrSensorReset() {
    int memoryAddress;
    for (int i = 0; i < ldrSensorNumberValuesSaved; i++) {
        memoryAddress = ldrSensorFirstValueMemoryAddress + i * intSize;
        EEPROM.put(memoryAddress, 0);
    }
}
