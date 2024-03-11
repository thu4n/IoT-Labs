#define LED_PINS {2, 3, 4}
#define POT_PIN A0

int ledPins[3] = LED_PINS;
int ledStates[3] = {LOW, LOW, LOW};
int potValue = 0;
int speed = 0;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POT_PIN);
  speed = map(potValue, 0, 1023, 1, 3);
  Serial.print("Pot value: ");
  Serial.print(potValue);
  Serial.print(" | Speed: ");
  Serial.println(speed);

  for (int i = 0; i < 3; i++) {
    if (speed == 1) {
      ledStates[i] = (millis() / 500) % 2;
    } else if (speed == 2) {
      ledStates[i] = (millis() / 250) % 2;
    } else if (speed == 3) {
      ledStates[i] = (millis() / 100) % 2;
    }
    digitalWrite(ledPins[i], ledStates[i]);
  }
}
