const int pirPin = 7;    // Pin connected to the PIR sensor's output
const int ledPin1 = 8;   // Pin connected to the first LED
const int ledPin2 = 9;   // Pin connected to the second LED

void setup() {
  Serial.begin(9600);    // Initialize serial communication
  pinMode(pirPin, INPUT);    // Set PIR sensor pin as input
  pinMode(ledPin1, OUTPUT);  // Set LED pins as output
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  int sensorValue = digitalRead(pirPin);  // Read sensor value

  if (sensorValue == HIGH) {    // If motion detected
    Serial.println("Motion detected!");
    blinkLEDs();    // Call function to blink LEDs
  } else {
    Serial.println("No motion detected.");
    // Turn off LEDs when no motion is detected
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }

  delay(500);  // Short delay to avoid overwhelming serial output
}

void blinkLEDs() {
  // Blink LEDs continuously until no motion is detected
  while (digitalRead(pirPin) == HIGH) {
    digitalWrite(ledPin1, HIGH); // Turn on LED 1
    digitalWrite(ledPin2, LOW);  // Turn off LED 2
    delay(500);  // Wait for 500 milliseconds
    digitalWrite(ledPin1, LOW);  // Turn off LED 1
    digitalWrite(ledPin2, HIGH); // Turn on LED 2
    delay(500);  // Wait for 500 milliseconds
  }
}
