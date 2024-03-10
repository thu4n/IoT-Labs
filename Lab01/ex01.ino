const int buttonPin = 2;  // Chân kết nối nút nhấn
const int ledCount = 12;  // Số lượng đèn LED
int leds[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0};  // Chân kết nối đèn LED
int buttonState = 0;     // Trạng thái nút nhấn
int ledIndex = 0;        // Index của đèn LED hiện tại

void setup() {
  // Khai báo chân làm OUTPUT cho đèn LED
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // Khai báo chân làm INPUT cho nút nhấn
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Đọc trạng thái của nút nhấn
  buttonState = digitalRead(buttonPin);

  // Nếu nút nhấn được nhấn
  if (buttonState == HIGH) {
    // Chờ nút nhấn được thả
    while (digitalRead(buttonPin) == HIGH);

    // Tăng index của đèn LED
    ledIndex++;

    // Nếu index vượt quá số lượng đèn, đặt lại về 0
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

    // Đợi một khoảng thời gian trước khi tiếp tục
    delay(500);
  }
}
