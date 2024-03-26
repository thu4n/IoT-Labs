#include "MQ135.h"
 
#define PIN_MQ135 A0
#define LED 13

MQ135 mq135_sensor = MQ135(PIN_MQ135);
 
void blynk(int milis) {
    digitalWrite(LED, HIGH);
    delay(milis);
    digitalWrite(LED, LOW);
    delay(milis);
    digitalWrite(LED, HIGH);
    delay(milis);
    digitalWrite(LED, LOW);
    delay(milis);
    digitalWrite(LED, HIGH);
    delay(milis);
    digitalWrite(LED, LOW);
    delay(milis);
}

void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
}
 
void loop() {
    float resistance = mq135_sensor.getResistance();
    float ppm = mq135_sensor.getPPM();
    
    Serial.print("Resistance: ");
    Serial.print(resistance);
    Serial.print("\t PPM: ");
    Serial.print(ppm);
    Serial.println(" ppm");

    if (ppm > 50 && ppm <= 150) {
        Serial.println("Moderate air quality!");
        blynk(500);
    } else if (ppm > 150) {
        Serial.println("Unhealthy air quality!");
        blynk(100);
    } else {
        Serial.println("Good air quality!");
        blynk(1000);
    }
}