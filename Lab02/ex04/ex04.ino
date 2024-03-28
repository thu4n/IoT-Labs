#include <DHT.h>

#define DHTPIN 2     // Chân digital được sử dụng cho cảm biến DHT11
#define DHTTYPE DHT11   // Loại cảm biến (DHT11 hoặc DHT22 hoặc DHT21)

#define FAN_PIN_1 5    // Chân digital cho đèn LED biểu thị quạt mức 1
#define FAN_PIN_2 6    // Chân digital cho đèn LED biểu thị quạt mức 2
#define FAN_PIN_3 7    // Chân digital cho đèn LED biểu thị quạt mức 3

#define TEMP_THRESHOLD_H1 38    // Ngưỡng nhiệt độ cao
#define TEMP_THRESHOLD_H2 40    // Ngưỡng nhiệt độ cao
#define TEMP_THRESHOLD_H3 42    // Ngưỡng nhiệt độ cao
#define TEMP_THRESHOLD_NORMAL 35  // Ngưỡng nhiệt độ trở lại bình thường
#define HUMIDITY_THRESHOLD_HIGH 80  // Ngưỡng độ ẩm cao

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    pinMode(FAN_PIN_1, OUTPUT);
    pinMode(FAN_PIN_2, OUTPUT);
    pinMode(FAN_PIN_3, OUTPUT);

    dht.begin();
    Serial.begin(9600);
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    if (temperature > TEMP_THRESHOLD_NORMAL && temperature <= TEMP_THRESHOLD_H1) {
        Serial.println("Temperature is little high");
        digitalWrite(FAN_PIN_1, HIGH);
        digitalWrite(FAN_PIN_2, LOW);
        digitalWrite(FAN_PIN_3, LOW);
    } else if (temperature > TEMP_THRESHOLD_H1 && temperature <= TEMP_THRESHOLD_H2) {
        Serial.println("Temperature is high");
        digitalWrite(FAN_PIN_1, HIGH);
        digitalWrite(FAN_PIN_2, HIGH);
        digitalWrite(FAN_PIN_3, LOW);
    } else if (temperature > TEMP_THRESHOLD_H2 && temperature <= TEMP_THRESHOLD_H3) {
        Serial.println("Temperature is too high");
        digitalWrite(FAN_PIN_1, HIGH);
        digitalWrite(FAN_PIN_2, HIGH);
        digitalWrite(FAN_PIN_3, HIGH);
    } else {
        Serial.println("Temperature is normal");
        digitalWrite(FAN_PIN_1, LOW);
        digitalWrite(FAN_PIN_2, LOW);
        digitalWrite(FAN_PIN_3, LOW);
    }

    if ((FAN_PIN_1 == HIGH || FAN_PIN_2 == HIGH || FAN_PIN_3 == HIGH) && humidity > HUMIDITY_THRESHOLD_HIGH) {
        Serial.println("Server cooled down, turn off the fan");
        digitalWrite(FAN_PIN_1, LOW);
        digitalWrite(FAN_PIN_2, LOW);
        digitalWrite(FAN_PIN_3, LOW);
    }

    Serial.println("=====================================");

  delay(2000);  // Chờ 2 giây trước khi đọc dữ liệu từ cảm biến lại
}