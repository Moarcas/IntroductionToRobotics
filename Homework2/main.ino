unsigned int lastDebounceTime = 0;
const unsigned int debounceDelay = 50;

int buttonValueRead = 0;
int x = 0;

void setup() {
  Serial.begin(9600);
}

class Button {
  private:
    int pin;
    int lastValueRead;
    byte state;
 
  public:
    Button(int pin) {
      pinMode(pin, INPUT_PULLUP);
      this->pin = pin;
      lastValueRead = 0;
      state = LOW; 
    }
    bool isPressed() {
      bool pressed = false;
      buttonValueRead = !digitalRead(this->pin);
      if (buttonValueRead != this->lastValueRead) {
        lastDebounceTime = millis();
      }
      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (this->state != buttonValueRead) {
          this->state = buttonValueRead;
          if (this->state == HIGH) {
            pressed = true;
          }
        }
      }
      this->lastValueRead = buttonValueRead;
      return pressed;
    }
};

class Led {
  private:
    int pin;
    byte state;

  public:
    Led(int pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
    }

    void changeState() {
      state = !state;
      digitalWrite(pin, state);
    }

    void turnOn() {
      state = HIGH;
      digitalWrite(pin, state);
    }

    byte getState() {
      return state;
    }
};

class Buzzer {
  private: 
    int pin;
    byte state;

  public:
    Buzzer(int pin) {
      this->pin = pin;
      pinMode(pin, OUTPUT);
    }

    void changeState() {
      state = !state;
      digitalWrite(pin, state);
    }

    void turnOn() {
      digitalWrite(pin, HIGH);
    }

    void turnOff() {
      digitalWrite(pin, LOW);
    }
};

class Elevator {
  private:
    Button* buttons[3]; 
    Led* leds[3]; // red leds
    Buzzer* buzzer;
    Led* greenLed;
    int currentFloor;
    int targetFloor;
    unsigned long moveStartTime;
    unsigned long greenLedStart;
    unsigned int moveTime;
    unsigned int ledTime;
    unsigned int greenLedTime;
    bool greenLedReady;

  public:
    Elevator(Button* buttons[], Led* leds[], Buzzer* buzzer, Led* greenLed) {
      for (int i = 0; i < 3; i++) {
        this->buttons[i] = buttons[i];
        this->leds[i] = leds[i];
      }
      this->buzzer = buzzer;
      this->greenLed = greenLed;
      moveTime = 3500;
      ledTime = 1500;
      greenLedTime = 500;
      moveStartTime = 0;
      greenLedStart = 0;
      currentFloor = 0;
      greenLedReady = false;
      leds[currentFloor]->changeState();
      greenLed->changeState();
    }

    bool buttonPressed() {
      for (int i = 0; i < 3; i++) {
        if (currentFloor != i && buttons[i]->isPressed()) {
          targetFloor = i; 
          greenLedReady = false;
          moveStartTime = millis(); // save the time when the button was pressed
          return true;
        }
      }
      return false;
    }

    void turnOffCurrentLed() {
      if (millis() - moveStartTime > ledTime) {
          leds[currentFloor]->changeState();
          greenLedReady = true;
        }
    }

    void changeFloor() {
      x = (currentFloor < targetFloor);
      currentFloor = currentFloor + x + (-1 * (1 - x));
      leds[currentFloor]->changeState(); // open the led
      if (isMoving() == false) {
        buzzer->turnOff();
        greenLed->turnOn();
      }
      moveStartTime = millis();
    }

    void moveOneFloor() {
      tone(12, 2500, 1000); 
      buzzer->turnOn();
      if (leds[currentFloor]->getState() == 1) {
        turnOffCurrentLed();
      } else if (millis() - moveStartTime > moveTime) {
        changeFloor();
      } 
      if (greenLedReady && millis() - greenLedStart > greenLedTime) {
        greenLed->changeState();
        greenLedStart = millis();
      }
    }

    bool isMoving() {
      return currentFloor != targetFloor;
    }
};

Button button1(2), button2(3), button3(4);
Led led1(8), led2(9), led3(10), greenLed(11);
Buzzer buzzer(12);

Button* buttons[] = {&button1, &button2, &button3};
Led* leds[] = {&led1, &led2, &led3};

Elevator elevator(buttons, leds, &buzzer, &greenLed);

void loop() {
  if (elevator.isMoving() || elevator.buttonPressed()) {
    elevator.moveOneFloor(); 
  }
}

