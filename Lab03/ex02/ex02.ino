#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <BH1750.h>
#include <Wire.h>
#include <ArduinoJson.h>

BH1750 lightMeter;

const char* ssid = "TheCupsCoffee";
const char* password = "Thecups2022";

const char* serverName = "http://192.168.1.40:8080/sensor";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

const int echoPin = D7; // Echo Pin
const int trigPin = D6; // Trigger Pin
const int ledPins[] = {D3, D4, D5};

int light = 0;
long distance, duration;
int ledNum = 0;
bool dis1 = true;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  lightMeter.begin();

  for (int i = 0; i < 5; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      readDistance();
      readLight();

      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");
      String jsonData = "{\"error\":false,\"message\":\"\",\"data\":{\"distance\":" + String(distance) + ",\"light\":" + String(light) + "}}";
      int httpResponseCode = http.POST(jsonData);

      String payload = "";
      if (httpResponseCode > 0) {
        payload = http.getString();
      }

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("Data: ");
      Serial.println(payload);
      JsonDocument doc;
      deserializeJson(doc, payload);
      ledNum = doc["lightsOn"];
      Serial.print("LED num: ");
      Serial.println(ledNum);
      Serial.println("=====================================");

      if (ledNum == 0) {
        for (int i = 0; i < 3; i++) {
          digitalWrite(ledPins[i], LOW);
        }
      } else {
        for (int i = 0; i < 3; i++) {
          digitalWrite(ledPins[i], LOW);
        }
        for (int i = 0; i < ledNum; i++) {
          digitalWrite(ledPins[i], HIGH);
        }
      }
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void readDistance() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void readLight() {
  light = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.println(light);
}