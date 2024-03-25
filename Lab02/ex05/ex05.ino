const int pirPin = 7;  // Pin connected to the PIR sensor's output

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(pirPin, INPUT);  // Set PIR sensor pin as input
}

void loop() {
  int sensorValue = digitalRead(pirPin);  // Read sensor value

  if (sensorValue == HIGH) {  // If motion detected
    Serial.println("Motion detected!");
  } else {
    Serial.println("No motion detected.");
  }

  delay(500);  // Short delay to avoid overwhelming serial output
}
