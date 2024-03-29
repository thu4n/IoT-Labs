#include <Wire.h>
#include <BH1750.h>

BH1750 lightSensor;

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int buttonPin = 12;
const int lightThreshold = 200; // Tùy chỉnh ngưỡng ánh sáng

int currentMode = 0;
int numLedsOn = 0;

void setup() {
  Serial.begin(9600);
  
  lightSensor.begin();
  
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(buttonPin, HIGH);
}

void loop() {
  int lightValue = lightSensor.readLightLevel();
  
  // Xác định chế độ đèn
  if (digitalRead(buttonPin) == LOW) {
    currentMode++;
    if (currentMode > 1) {
      currentMode = 0;
    }
    Serial.println("Mode: ", currentMode);
    delay(500); // Chống rung nút
  }
  
  // Điều chỉnh số lượng đèn LED
  switch (currentMode) {
    case 0: // Chế độ 5 đèn
        numLedsOn = map(lightValue, lightThreshold, 65535, 0, 10);
        if(numLedsOn > 5){
            numLedsOn = 5;
        }
      break;
    case 1: // Chế độ 10 đèn
      numLedsOn = map(lightValue, lightThreshold, 65535, 0, 10);
        if(numLedsOn > 10){
            numLedsOn = 10;
        }
      break;
  }
  
  // Bật/tắt đèn LED
  for (int i = 0; i < 10; i++) {
    if (i < numLedsOn) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  
