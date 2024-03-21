const int triggerPin = 13;
const int echoPin = 12;
const int ledPin = 9;
long duration;
int distance;
void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  // Tính toán khoảng cách dựa trên thời gian
  distance = duration * 0.034 / 2;
  
  // Hiển thị khoảng cách qua Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Điều khiển đèn LED dựa trên khoảng cách
  if (distance >= 0 && distance < 20) {
    
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  } else if (distance >= 20 && distance < 40) {
    
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
  } else if (distance >= 40 && distance < 60) {
    
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(600);
  } else if (distance >= 60 && distance < 80) {
    
    digitalWrite(ledPin, HIGH);
    delay(900);
    digitalWrite(ledPin, LOW);
    delay(900);
  } else if (distance >= 80) {
  
    digitalWrite(ledPin, HIGH);
    delay(1200);
    digitalWrite(ledPin, LOW);
    delay(1200);
  }
}