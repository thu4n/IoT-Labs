const int pirPin = 7;
const int ledPin1 = 8;
const int ledPin2 = 9;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  int sensorValue = digitalRead(pirPin);

  if (sensorValue == HIGH) {
    Serial.println("Motion detected!");
    blinkLEDs();
  } else {
    Serial.println("No motion detected.");
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }

  delay(500);  // Short delay to avoid overwhelming serial output
}

void blinkLEDs() {
  // Blink LEDs continuously until no motion is detected
  while (digitalRead(pirPin) == HIGH) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    delay(500);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    delay(500);
  }
}
