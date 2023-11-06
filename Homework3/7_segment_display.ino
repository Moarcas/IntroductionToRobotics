const bool commonAnode = false;

// Pins
const int pinSW = 2;
const int pinX = A0;
const int pinY = A1; 

const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

// Joystick
const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;
const int maxThreshold = 600;
const int minThreshold = 400;

bool joyMoved = false;
int xValue = 0;
int yValue = 0;
int joyDirection;

// Button
const int buttonResetThresholdTime = 1000;
const int buttonDebounceDelay = 50;

unsigned long lastButtonPressTime = 0; 
int buttonState = 0;
int buttonLastValueRead = 0; 

// Segment
const int segSize = 8;
const int segmentChangeStateThreshold = 300;  // segment blinking frequncy = (1 / segmentChangeStateThreshold) 
const int indexSegA = 0;
const int indexSegB = 1;
const int indexSegC = 2;
const int indexSegD = 3;
const int indexSegE = 4;
const int indexSegF = 5;
const int indexSegG = 6;
const int indexDP = 7;
// nextSegment[currentSegment][joyDirection]
const byte nextSegment[segSize][4] = {
  {indexSegA, indexSegG, indexSegF, indexSegB},   // segment a
  {indexSegA, indexSegG, indexSegF, indexSegB},   // segment b
  {indexSegG, indexSegD, indexSegE, indexDP},     // segment c
  {indexSegG, indexSegD, indexSegE, indexSegC},   // segment d
  {indexSegG, indexSegD, indexSegE, indexSegC},   // segment e
  {indexSegA, indexSegG, indexSegF, indexSegB},   // segment f
  {indexSegA, indexSegD, indexSegG, indexSegG},   // segment g
  {indexDP,   indexDP,   indexSegC, indexDP}      // semgnet DP
  //up        down       left       right
};
const int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
// 0     1     2     3     4     5     6      7
};
int segmentInitialState[segSize] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long lastSegmentStateChangeTime = 0;
int currentSegmentIndex = indexDP;
int currentSegmentState = 1; 


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }

  pinMode(pinSW, INPUT_PULLUP);
  
  if (commonAnode == true) {
    currentSegmentState = 0;
    for (int i = 0; i < segSize; i++)  {
      segmentInitialState[i] = 1;
    }  
  }
}

void changeStateSegment(int segmentIndex) {
  Serial.println(segmentIndex);
  if (millis() - lastSegmentStateChangeTime > segmentChangeStateThreshold) {
    lastSegmentStateChangeTime = millis();
    currentSegmentState = !currentSegmentState;
    digitalWrite(segments[segmentIndex], currentSegmentState); 
  }
}

int calculateNextMove(int xValue, int yValue) {
  if (xValue < minThreshold) {
    return left;
  }
  if (xValue > maxThreshold) {
    return right;
  }
  if (yValue < minThreshold ) {
    return down;
  }
  if (yValue > maxThreshold) {
    return up;
  }
  joyMoved = false;
  return -1;
}

bool buttonIsPressed() {
  bool pressed = false;
  int buttonValueRead = !digitalRead(pinSW);
  if (buttonValueRead != buttonLastValueRead) {
    lastButtonPressTime = millis();
  }
  if (millis() - lastButtonPressTime > buttonDebounceDelay) {
    if (buttonState != buttonValueRead) {
      buttonState = buttonValueRead;
      if (buttonState == HIGH) {
        pressed = true;
      }
    }
  }
  buttonLastValueRead = buttonValueRead;
  return pressed;
}

bool resetIsPressed() {
  bool reset = false;
  int buttonValueRead = !digitalRead(pinSW);
  if (buttonValueRead != buttonLastValueRead) {
    lastButtonPressTime = millis();
  }
  if (millis() - lastButtonPressTime > buttonResetThresholdTime) {
    if (buttonValueRead == 1) {
      reset = true;
    }
  }
  buttonLastValueRead = buttonValueRead;
  return reset;
}

void reset() {
  for (int i = 0; i < segSize; i++) {
    segmentInitialState[i] = 0;
    digitalWrite(segments[i], LOW);
  }
  currentSegmentIndex = 7;
}

void loop() {
  changeStateSegment(currentSegmentIndex);

  xValue = analogRead(pinX);
  yValue = 1023 - analogRead(pinY);

  joyDirection = calculateNextMove(xValue, yValue);

  if (joyDirection != -1 && joyMoved == false) {
    joyMoved = true;
    digitalWrite(segments[currentSegmentIndex], segmentInitialState[currentSegmentIndex]);
    currentSegmentIndex = nextSegment[currentSegmentIndex][joyDirection];
  }

  if (buttonIsPressed()) {
    segmentInitialState[currentSegmentIndex] = !segmentInitialState[currentSegmentIndex];
  }

  if (resetIsPressed()) {
    reset();
  }
}

