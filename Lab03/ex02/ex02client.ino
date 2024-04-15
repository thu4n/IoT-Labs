#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <NewPing.h>
#include <BH1750.h>

const char* ssid = "Daivjppro";
const char* password = "123456780";
const char* serverAddress = "http://localhost:8080/sensor";

const int triggerPin = D1;  // Chân trigger của cảm biến khoảng cách HC-SR04 (GPIO 5)
const int echoPin = D0;     // Chân echo của cảm biến khoảng cách HC-SR04 (GPIO 16)
const int lightSensorPin = D3; // Chân SDA của cảm biến ánh sáng BH1750 (GPIO 0)
const int light1Pin = D5;   // Chân digital của đèn 1 (GPIO 14)
const int light2Pin = D6;   // Chân digital của đèn 2 (GPIO 12)
const int light3Pin = D7;   // Chân digital của đèn 3 (GPIO 13)

WiFiClient client;
HTTPClient http;
NewPing sonar(triggerPin, echoPin);
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Wire.begin(D3, D2); // Khởi động giao tiếp I2C với SDA là D3 và SCL là D2

  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(light3Pin, OUTPUT);

  lightMeter.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float distance = readDistance();
    float lightIntensity = readLightIntensity();

    // Tạo JSON payload
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["distance"] = distance;
    jsonDoc["lightIntensity"] = lightIntensity;

    // Gửi yêu cầu HTTP POST
    if (http.begin(client, serverAddress)) {
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(jsonDoc.as<String>());

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          String response = http.getString();
          // Xử lý phản hồi từ server nếu cần
          Serial.println("Server response: " + response);
        }
      } else {
        Serial.println("HTTP request failed");
      }
      
      http.end();
    } else {
      Serial.println("Unable to connect to server");
    }

    delay(5000); // Đợi 5 giây trước khi gửi yêu cầu tiếp theo
  } else {
    Serial.println("WiFi not connected");
  }
}

float readDistance() {
  delay(50); // Đợi 50ms trước khi đọc cảm biến khoảng cách
  unsigned int distance_cm = sonar.ping_cm();
  return distance_cm;
}

float readLightIntensity() {
  float lightIntensity = lightMeter.readLightLevel();
  return lightIntensity;
}
