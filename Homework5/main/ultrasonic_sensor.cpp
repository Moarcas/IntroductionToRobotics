#include "ultrasonic_sensor.h"
#include "Arduino.h"
#include <EEPROM.h>

const int ultrasonicSensorValueMemoryAddress = 32;
const int thresholdMemoryAddress = 20;
const int samplingIntervalMemoryAddress = 22;
const int ldrPin = A0;
const int trigPin = 6;
const int echoPin = 5;
static unsigned long lastTimeRead;
static bool showOutput = false;

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

void ultrasonicSensorProcessing() {
    if (ultrasonicSensorReadyToStart()) {
        EEPROM.put(ultrasonicSensorValueMemoryAddress, ultrasonicSensorReadValue());
    
        if (showOutput) {
            Serial.print("      ->Ultrasonic Sensor Value: ");
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
    int ultrasonicSensorValue;
    EEPROM.get(ultrasonicSensorValueMemoryAddress, ultrasonicSensorValue);
    return ultrasonicSensorValue;
}

bool ultrasonicSensorAlert() {
    return ultrasonicSensorGetValue() > ultrasonicSensorGetThreshold();
}

void ultrasonicSensorShowOutput(bool show) {
    showOutput = show;
}

