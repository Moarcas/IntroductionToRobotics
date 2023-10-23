const int potPinRed = A0;
const int potPinGreen = A1;
const int potPinBlue = A2;

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

int potValueRed = 0;
int potValueGreen = 0;
int potValueBlue = 0;

int valueRed = 0;
int valueGreen = 0;
int valueBlue = 0;

void setup() {
  Serial.begin(9600); // Inițializare serial pentru afișarea datelor în monitorul serial

  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT);
}

void loop() {
  potValueRed = analogRead(potPinRed);
  potValueGreen = analogRead(potPinGreen);
  potValueBlue = analogRead(potPinBlue);

  valueRed = map(potValueRed, 0, 1023, 0, 255);
  valueGreen = map(potValueGreen, 0, 1023, 0, 255);
  valueBlue = map(potValueBlue, 0, 1023, 0, 255);

  analogWrite(redPin, valueRed);
  analogWrite(greenPin, valueGreen);
  analogWrite(bluePin, valueBlue);

  delay(10);
}