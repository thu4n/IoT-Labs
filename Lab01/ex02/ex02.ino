// Khai báo chân LED
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// Khai báo chân biến trở
const int potPin = A0;

// Biến lưu trữ giá trị biến trở
int potValue = 0;

// Biến lưu trữ tốc độ sáng đèn
int speed = 0;

void foo(int x) {
    digitalWrite(led1, HIGH);
    delay(x);
    digitalWrite(led1, LOW);
    
    digitalWrite(led2, HIGH);
    delay(x);
    digitalWrite(led2, LOW);
    
    digitalWrite(led3, HIGH);
    delay(x);
    digitalWrite(led3, LOW);

    digitalWrite(led2, HIGH);
    delay(x);
    digitalWrite(led2, LOW);
    
    digitalWrite(led1, HIGH);
    delay(x);
    digitalWrite(led1, LOW);
}

void setup() {
  // Khởi tạo Serial Monitor
  Serial.begin(9600);

  // Khởi tạo các chân LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Khởi tạo chân biến trở
  pinMode(potPin, INPUT);
}

void loop() {
  // Đọc giá trị biến trở
  potValue = analogRead(potPin);

  // Xác định tốc độ sáng đèn
  if (potValue < 333) {
    speed = 1;
  } else if (potValue < 666) {
    speed = 2;
  } else {
    speed = 3;
  }

  // Hiển thị giá trị biến trở và tốc độ sáng đèn
  Serial.print("Giá trị biến trở: ");
  Serial.print(potValue);
  Serial.print(" | Tốc độ sáng đèn: ");
  Serial.println(speed);

  // Điều khiển đèn LED
  switch (speed) {
    case 1:
      foo(500);
      break;
    case 2:
      foo(250);
      break;
    case 3:
      foo(100);
      break;
  }
}
