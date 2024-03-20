#include <LiquidCrystal_I2C.h>

const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int buttonPins[] = {A0, A1, A2};

LiquidCrystal_I2C lcd(0x27,  16, 2);

int score = 0; 
int level = 1;
bool isTimeOut = false;
int correctButton;
unsigned long startTime = millis();

void setup() {
  lcd.begin();					
  lcd.backlight();
  lcd.setCursor(0,0);
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  Serial.begin(9600);
  setLevel(1);
}

void loop() {
  playGame();
}

void playGame() {
  int ledCount = random(1,11);// random chỗ này
  correctButton = ledCount % 3;
  flashLEDs(ledCount, ledPins); // Nháy đèn
  Serial.print("Button: ");
  Serial.println(correctButton);
  delay(4000 - (level * 1000));
  checkButtons();
  // Hết thời gian, reset cấp độ và điểm số
}

void checkButtons() {
  // Kiểm tra trạng thái nút bấm và cộng hoặc trừ điểm
  Serial.println(digitalRead(buttonPins[1]));
  isTimeOut = false;
  if (digitalRead(buttonPins[0]) == HIGH && correctButton == 0) {
    score++;
    level++;
    setLevel(level);
    displayScore("+1");
  } else if (digitalRead(buttonPins[1]) == HIGH && correctButton == 1) {
    score++;
    level++;
    setLevel(level);
    displayScore("+1");
  } else if (digitalRead(buttonPins[2]) == HIGH && correctButton == 2) {
    score++;
    level++;
    setLevel(level);
    displayScore("+1");
  } else {
    // Trường hợp không chọn nút hoặc chọn sai
    score--;
    if (score == -1) {
      score = 0;
    }
    setLevel(1);
    displayScore("-1");
  } 
}

void flashLEDs(int ledCount,const int ledPins[]) {
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
  if (level > 3) {
    level = 3;
  }
  lcd.clear();
  lcd.print("Lv: ");
  lcd.print(level);
  lcd.print(" Score: ");
  lcd.print(score);
}

void displayScore(String message) {
  // Hiển thị điểm số được cộng hoặc trừ trên LCD
  lcd.setCursor(0, 1);
  lcd.print(message);
}