const int pirPin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
}

void loop() {
  int sensorValue = digitalRead(pirPin);

  if (sensorValue == HIGH) {
    Serial.println("Motion detected!");
  } else {
    Serial.println("No motion detected.");
  }

  delay(500);  // Short delay to avoid overwhelming serial output
}
