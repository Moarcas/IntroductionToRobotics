#include "ultrasonic_sensor.h"
#include "Arduino.h"
#include <EEPROM.h>

const int ultrasonicSensorNumberValuesSaved = 10;
const int ultrasonicSensorFirstValueMemoryAddress = 100;
const int thresholdMemoryAddress = 20;
const int samplingIntervalMemoryAddress = 22;
const int trigPin = 6;
const int echoPin = 5;
const int intSize = 2;
static unsigned long lastTimeRead;
static bool showOutput = false;
static int indexValueToSave;

void setupUltrasonicSensor() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int ultrasonicSensorReadValue() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return pulseIn(echoPin, HIGH) * 0.034/2;
}

void ultrasonicSensorChangeThreshold(int newThreshold) {
    EEPROM.put(thresholdMemoryAddress, newThreshold); 
}

void ultrasonicSensorChangeSamplingInterval(int newSamplingInterval) {
    EEPROM.put(samplingIntervalMemoryAddress, newSamplingInterval);
}

bool ultrasonicSensorReadyToStart() {
    return (millis() - lastTimeRead) > (ultrasonicSensorGetSamplingInterval() * 1000);
}

void saveValueInMemory(int value) {
    int memoryAddress = ultrasonicSensorFirstValueMemoryAddress + indexValueToSave * intSize;
    indexValueToSave++;
    EEPROM.put(memoryAddress, value);
    if (indexValueToSave == ultrasonicSensorNumberValuesSaved) 
        indexValueToSave = 0;
}

void ultrasonicSensorProcessing() {
    if (ultrasonicSensorReadyToStart()) {
        saveValueInMemory(ultrasonicSensorReadValue());
    
        if (showOutput) {
            Serial.print(F("      ->Ultrasonic Sensor Value: "));
            Serial.println(ultrasonicSensorGetValue());
        }
            
        lastTimeRead = millis();
    }
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

int ultrasonicSensorGetValue() {
    int memoryAddress = ultrasonicSensorFirstValueMemoryAddress + ((ultrasonicSensorNumberValuesSaved + indexValueToSave - 1) % ultrasonicSensorNumberValuesSaved) * intSize;
    int ultrasonicSensorValue;
    EEPROM.get(memoryAddress, ultrasonicSensorValue);
    return ultrasonicSensorValue;
}

bool ultrasonicSensorAlert() {
    return ultrasonicSensorGetValue() > ultrasonicSensorGetThreshold();
}

void ultrasonicSensorShowOutput(bool show) {
    showOutput = show;
}

void ultrasonicSensorShowLoggedData() {
    int memoryAddress;
    int ultrasonicSensorValue;
    Serial.print(F("    ->Ultrasonic Sensor Logged Data: "));
    for (int i = 1; i <= ultrasonicSensorNumberValuesSaved; i++) {
        memoryAddress = ultrasonicSensorFirstValueMemoryAddress + ((ultrasonicSensorNumberValuesSaved - i + indexValueToSave) % ultrasonicSensorNumberValuesSaved) * intSize;
        EEPROM.get(memoryAddress, ultrasonicSensorValue);
        Serial.print(ultrasonicSensorValue);
        Serial.print(" ");
    }
    Serial.println();
}

void ultrasonicSensorReset() {
    int memoryAddress;
    for (int i = 0; i < ultrasonicSensorNumberValuesSaved; i++) {
        memoryAddress = ultrasonicSensorFirstValueMemoryAddress + i * intSize;
        EEPROM.put(memoryAddress, 0);
    }
}
