#include <Wire.h>
#include <BH1750.h>

BH1750 lightSensor;

const int ledPins[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int buttonPin = 3;
const int lightThreshold = 1000; // Tùy chỉnh ngưỡng ánh sáng

bool currentMode = 0;
int numLedsOn = 1;
int maxLedsOn = 5;
boolean first = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  lightSensor.begin();
  
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(buttonPin, HIGH);
}

void loop() {
  Serial.println("==============begin===============");
  int lightValue = lightSensor.readLightLevel();

  // Xác định chế độ đèn
  delay(500);
  if (digitalRead(buttonPin) == LOW && first == false) {
    currentMode = 0;
    Serial.println("1st pressed");
    first = true;
    delay(500);
    if (digitalRead(buttonPin) == LOW && first == true) {
      currentMode = 1;
      Serial.println("2nd pressed");
      first = false;
    }
  }

  Serial.println(currentMode);
  first = false;
  maxLedsOn = map(lightValue, 0, 1000, 0, 10);
  
  // Điều chỉnh số lượng đèn LED
  switch (currentMode) {
    case 0: // Chế độ 5 đèn
        if(maxLedsOn > 5){
          maxLedsOn = 5;
        }
        numLedsOn = 5 - maxLedsOn;
      break;
    case 1: // Chế độ 10 đèn
        if(maxLedsOn > 10){
            maxLedsOn = 10;
        }
        numLedsOn = 10 - maxLedsOn;
      break;
  }

  Serial.println(numLedsOn);
  Serial.println(maxLedsOn);
  
  // Bật/tắt đèn LED
  for (int i = 0; i < 10; i++) {
    if (i < numLedsOn) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  Serial.println("====================");
}
  
