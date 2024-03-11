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

    // Lần lượt sáng từng đèn
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(100);
    }

    // Sáng lượng đèn bằng với số được random
    for (int i = 0; i < 6; i++) {
      digitalWrite(ledPins[i], (i + 1) <= randomNumber ? HIGH : LOW);
    }
    delay(1000);

    // Bật tắt tất cả đèn led 6 lần
    for (int i = 0; i < 6; i++)
    {
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      delay(100);
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPins[i], LOW);
      }
      delay(100);
    }
    delay(1000);
  }
}
