#include <Wire.h>
#include <BH1750.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Daivjppro";
const char* password = "123456780";
const char* mqtt_server = "mqtt.thingsboard.cloud";
const char* topic = "v1/devices/me/telemetry";
const String username = "1n2DNxT7sDDA0ycBziSe";

// Khai báo biến toàn cục cho địa chỉ của cảm biến BH1750
uint8_t bh1750Address = 0x23;

// Khởi tạo đối tượng cảm biến BH1750
BH1750 lightMeter;

// Khởi tạo đối tượng WiFi
WiFiClient espClient;

// Khởi tạo đối tượng MQTT
PubSubClient client(espClient);

// Khai báo chân GPIO cho đèn LED
const int ledPin1 = D3;
const int ledPin2 = D4;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", username.c_str(), NULL)) {
      Serial.println("connected");
      client.subscribe("v1/devices/me/rpc/request/+"); // Subscribe để nhận các yêu cầu từ Thingsboard
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);
  if (!lightMeter.configure(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("BH1750 configuration failed!");
  } else {
    Serial.println("BH1750 configured successfully!");
  }
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Đọc giá trị từ cảm biến BH1750
  float lux = lightMeter.readLightLevel();

  // Gửi giá trị lên MQTT
  char msg[50];
  snprintf (msg, 50, "{\"lux\":%.2f}", lux);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(topic, msg);

  delay(2000); // Chờ 2 giây trước khi gửi lại
}

// Hàm xử lý yêu cầu từ Thingsboard
void on_message(const char* topic, byte* payload, unsigned int length) {
  Serial.println("Message received from Thingsboard");
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (message.equals("0")) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    Serial.println("Both LEDs turned off");
  } else if (message.equals("1")) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    Serial.println("LED 1 turned on, LED 2 turned off");
  } else if (message.equals("2")) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    Serial.println("Both LEDs turned on");
  }
}
