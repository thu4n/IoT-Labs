#include <random>

const int ledPins[6] = {2, 3, 4, 5, 6, 7};
const int buttonPin = 8;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    int randomNumber = random(1, 7);
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], (i + 1) <= randomNumber ? HIGH : LOW);
    }
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(50);
      digitalWrite(ledPins[i], LOW);
    }
    delay(1000);
  }
}
