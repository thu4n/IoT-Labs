#include <LiquidCrystal.h>

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int buttonPins[] = {A0, A1, A2};
const int lcdPins[] = {12, 13, A4, A5};

LiquidCrystal lcd(lcdPins[0], lcdPins[1], lcdPins[2], lcdPins[3]);

int score = 0; 
int level = 1;
int correctButton;
unsigned long startTime;

void setup() {
  lcd.begin(16, 2);
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  setLevel(1);
}

void loop() {
  playGame();
}

void playGame() {
  int ledCount = random(1, 10);
  correctButton = ledCount % 3;
  flashLEDs(ledCount, ledPins); // Nháy đèn
  startTime = millis(); // Bắt đầu thời gian
  while (millis() - startTime < 4000 - (level * 1000)) {
    // Kiểm tra nút bấm
    checkButtons();
  }
  // Hết thời gian, reset cấp độ và điểm số
  level = 1;
  score = 0;
  lcd.clear();
  lcd.print("Game Over!");
  delay(2000);
  lcd.clear();
}

void checkButtons() {
  // Kiểm tra trạng thái nút bấm và cộng hoặc trừ điểm
  if (digitalRead(buttonPins[0]) == HIGH && correctButton == 1) {
    score++;
    setLevel(score % 3 + 1);
    displayScore("+1");
  } else if (digitalRead(buttonPins[1]) == HIGH && correctButton == 2) {
    score++;
    setLevel(score % 3 + 1);
    displayScore("+1");
  } else if (digitalRead(buttonPins[2]) == HIGH && correctButton == 3) {
    score++;
    setLevel(score % 3 + 1);
    displayScore("+1");
  } else if (millis() - startTime >= 4000 - (level * 1000)) {
    // Trường hợp không chọn nút hoặc chọn sai
    score--;
    setLevel(1);
    displayScore("-1");
  }
}

void flashLEDs(int ledCount, int ledPins[]) {
  // Bật `ledCount` đèn LED đầu tiên trong mảng `ledPins`.
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  // Tắt các đèn LED còn lại.
  for (int i = ledCount; i < 10; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void setLevel(int newLevel) {
  // Cài đặt cấp độ và hiển thị trên LCD
  level = newLevel;
  lcd.clear();
  lcd.print("Level: ");
  lcd.print(level);
  lcd.print(" Score: ");
  lcd.print(score);
}

void displayScore(String message) {
  // Hiển thị điểm số được cộng hoặc trừ trên LCD
  lcd.setCursor(0, 1);
  lcd.print(message);
}