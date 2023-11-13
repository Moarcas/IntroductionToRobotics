#include <EEPROM.h> //include the library
int counter = 0;

void setup() {
    Serial.begin(9600); //Start serial monitor
    EEPROM.get(0, counter);
    Serial.println(counter);
    counter++;
    EEPROM.put(0, counter);
}
void loop() {
}
