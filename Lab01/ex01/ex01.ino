const int buttonPin = 2; 
const int ledCount = 12;
int leds[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0};  // Chân kết nối đèn LED
int buttonState = 0;
int ledIndex = 0; // Index của đèn LED hiện tại

void setup() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    while (digitalRead(buttonPin) == HIGH);
    ledIndex++;

    // Nếu index vượt quá số lượng đèn, quay lại còn 1 đèn sáng
    if (ledIndex >= ledCount) {
      ledIndex = 0;
    }

    // Tắt tất cả các đèn LED
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(leds[i], LOW);
    }

    // Bật số lượng đèn LED tương ứng với giá trị index
    for (int i = 0; i <= ledIndex; i++) {
      digitalWrite(leds[i], HIGH);
    }
    delay(500);
  }
}