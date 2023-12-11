#include "map.h"
#include "player.h"
#include "joystick.h"
#include "bullet.h"
#include <LiquidCrystal.h>

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte customChar[8] = {
	0b10010,
	0b11011,
	0b00000,
	0b00000,
	0b10001,
	0b10001,
	0b11111,
	0b00000
};

const int pinContrast = 3;

int gameMap[mapSize][mapSize];

void setup() {
    Serial.begin(9600);

    setupMatrix();
    setupJoystick();

    generateMap(gameMap);
    generatePlayerPosition(gameMap);

    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hello, world!");
    pinMode(pinContrast, OUTPUT);
    lcd.createChar(1, customChar);
    lcd.setCursor(5, 1);
    lcd.write((byte)1);

    delay(1000);
}

void loop() {

    if (Serial.available()) {
      int contrast = Serial.parseInt();
      Serial.print("Am citit valoarea ");
      Serial.println(contrast);
      analogWrite(pinContrast, contrast);
    }

    lcd.setCursor(3, 1);
    // print the number of seconds since reset:
    lcd.print(millis() / 1000);

    showMap(gameMap);

    char direction = joystickMove();

    if (direction != 'n')
        movePlayer(gameMap, direction);
        changeMiniMapPosition(getPlayerPosition(), direction);

    if (buttonIsPressed())
        shoot(getPlayerPosition(), getPlayerOrientation());
}

