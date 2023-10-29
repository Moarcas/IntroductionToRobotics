unsigned long lastDebounceTime = 0;
const unsigned int debounceDelay = 50;

unsigned long lastFinishTime = 0;
const unsigned int elevatorDelay = 1000;

int buttonValueRead = 0;
int x = 0;

void setup() {
  Serial.begin(9600);
}

class Node {
  public:
    int floor;
    Node* next;
    Node() { next = 0; }
};

class Queue {
  public:
    Node* head;
    Node* tail;

  public:
    Queue() { head = 0; tail = 0; }

    bool isEmpty() {
      return head == 0;
    }

    void insert(int floor) { // le adaug la dreapta
      if (isEmpty()) {
        Node* newNode = new Node;
        newNode->floor = floor;
        newNode->next = 0;
        head = newNode;
        tail = newNode;
      } else {
        Node* newNode = new Node;
        tail->next = newNode;
        newNode->floor = floor;
        newNode->next = 0;
        tail = newNode;
      }
    }

    void deleteNode() { // le sterg la stanga
      // conventia este sa am mereu in coada un element, target-ul curent
      if (head->next) {
        Node* copy = head;
        head = head->next;
        delete copy;
      }
    }

    void print() {
      Node* x = head;
      while (x) {
        Serial.print(x->floor);
        x = x->next;
      }
      Serial.println();
    }

    int currentTarget() {
      return head->floor;
    }

    int lastTarget() {
      return tail->floor;
    }
};

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

    int getPin() {
      return pin;
    }
};

class Elevator {
  private:
    Button* buttons[3]; 
    Led* leds[3]; // red leds
    Buzzer* buzzer;
    Led* greenLed;
    int currentFloor;
    Queue targetFloors;
    unsigned long moveStartTime;
    unsigned long greenLedStartTime;
    unsigned int moveTime;
    unsigned int ledTime;
    unsigned int greenLedTime;
    unsigned int finishBuzzerTime;
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
      greenLedTime = 400;
      moveStartTime = 0;
      greenLedStartTime = 0;
      currentFloor = 0;
      targetFloors.insert(0);
      greenLedReady = false;
      leds[currentFloor]->changeState();
      greenLed->changeState();
    }

    void readButtonPressed() {
      for (int i = 0; i < 3; i++) {
        if (targetFloors.lastTarget() != i && buttons[i]->isPressed()) {          
          Serial.println("adaugare");
          targetFloors.print();
          targetFloors.insert(i);
          targetFloors.print();

          if (isMoving() == false) {
            Serial.println("stergere");
            targetFloors.print();
            targetFloors.deleteNode();
            targetFloors.print();
            moveStartTime = millis();
          }
        }
      }
    }

    void turnOffCurrentLed() {
      if (millis() - moveStartTime > ledTime) {
          leds[currentFloor]->changeState();
          greenLedReady = true;
        }
    }

    void changeFloor() {
      x = (currentFloor < targetFloors.currentTarget());
      currentFloor = currentFloor + x + (-1 * (1 - x));
      leds[currentFloor]->changeState(); // open the led
      if (isMoving() == false) {
        Serial.println("stergere");
        targetFloors.print();
        targetFloors.deleteNode();
        targetFloors.print();

        buzzer->turnOff();
        greenLed->turnOn();
        greenLedReady = false;
        lastFinishTime = millis();
        tone(buzzer->getPin(), 500);
        }

      moveStartTime = millis();
    }

    void moveOneFloor() {
      buzzer->turnOn();

      if (leds[currentFloor]->getState() == 1) {
        turnOffCurrentLed();
      } else if (millis() - moveStartTime > moveTime) {
        changeFloor();
      } 
      if (greenLedReady && millis() - greenLedStartTime > greenLedTime) {
        greenLed->changeState();
        greenLedStartTime = millis();
      }
    }

    bool isMoving() {
      return currentFloor != targetFloors.currentTarget();
    }

    void turnOffBuzzer() {
      buzzer->turnOff();
    }
};

Button button1(2), button2(3), button3(4);
Led led1(8), led2(9), led3(10), greenLed(11);
Buzzer buzzer(12);

Button* buttons[] = {&button1, &button2, &button3};
Led* leds[] = {&led1, &led2, &led3};

Elevator elevator(buttons, leds, &buzzer, &greenLed);

void loop() {
  elevator.readButtonPressed();
  if (millis() - lastFinishTime > elevatorDelay) {
    noTone(buzzer.getPin());
    if (elevator.isMoving()) {
      elevator.moveOneFloor(); 
    }
  }
}
