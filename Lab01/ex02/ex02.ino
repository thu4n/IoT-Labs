// Chân LED
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// Biến trở
const int potPin = A0;

// Giá trị biến trở
int potValue = 0;

int speed = 0;

void onAndOff(int x) {
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
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(potPin, INPUT);
}

void loop() {
  potValue = analogRead(potPin);

  if (potValue < 333) {
    speed = 1;
  } else if (potValue < 666) {
    speed = 2;
  } else {
    speed = 3;
  }

  Serial.print("Giá trị biến trở: ");
  Serial.print(potValue);
  Serial.print(" | Tốc độ sáng đèn: ");
  Serial.println(speed);

  switch (speed) {
    case 1:
      onAndOff(500);
      break;
    case 2:
      onAndOff(250);
      break;
    case 3:
      onAndOff(100);
      break;
  }
}
