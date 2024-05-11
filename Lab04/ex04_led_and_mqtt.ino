#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define WIFI_AP "Daivjppro"            // Tên mạng WiFi
#define WIFI_PASSWORD "123456780"    // Mật khẩu WiFi
#define TOKEN "1n2DNxT7sDDA0ycBziSe" // Token Thingsboard

#define LED1 D3   // Chân GPIO của LED1
#define LED2 D4   // Chân GPIO của LED2

const char* mqtt_server = "mqtt.thingsboard.cloud"; // MQTT broker của Thingsboard
const char* topic = "v1/devices/me/rpc/request/+";  // Chủ đề MQTT để nhận yêu cầu từ Thingsboard

WiFiClient espClient;         // Đối tượng client WiFi
PubSubClient client(espClient);  // Đối tượng client MQTT

boolean ledState[] = {false, false}; // Trạng thái của LED1 và LED2

void setup() {
  pinMode(LED1, OUTPUT);     // Đặt chân LED1 là đầu ra
  pinMode(LED2, OUTPUT);     // Đặt chân LED2 là đầu ra

  Serial.begin(115200);       // Bắt đầu giao tiếp với Serial
  setup_wifi();               // Khởi tạo kết nối WiFi
  client.setServer(mqtt_server, 1883);  // Thiết lập kết nối tới MQTT broker
  client.setCallback(callback);         // Thiết lập callback khi nhận được tin nhắn
}

void loop() {
  if (!client.connected()) {
    reconnect();                  // Thử kết nối lại nếu client MQTT không kết nối
  }
  client.loop();                  // Lắng nghe và xử lý tin nhắn MQTT
}

// Hàm khởi tạo kết nối WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_AP);

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Hàm callback khi nhận được tin nhắn từ ThingsBoard
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("On message");

  char json[length + 1];
  strncpy(json, (char*)payload, length);
  json[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);

  StaticJsonDocument<200> jsonBuffer;
  DeserializationError error = deserializeJson(jsonBuffer, json);

  if (error) {
    Serial.println("deserializeJson() failed");
    return;
  }

  String methodName = jsonBuffer["method"];

  if (methodName.equals("getGpioStatus")) {
    send_gpio_status(topic);
  } else if (methodName.equals("setGpioStatus")) {
    int pin = jsonBuffer["params"]["pin"];
    bool enabled = jsonBuffer["params"]["enabled"];
    set_gpio_status(pin, enabled);
  }
}

// Hàm gửi trạng thái GPIO về ThingsBoard
void send_gpio_status(char* topic) {
  StaticJsonDocument<200> jsonBuffer;
  JsonObject data = jsonBuffer.to<JsonObject>(); // Sử dụng biến cục bộ thay vì tham chiếu

  data[String(LED1)] = ledState[0] ? true : false;
  data[String(LED2)] = ledState[1] ? true : false;

  char payload[256];
  serializeJson(data, payload);

  String responseTopic = String(topic);
  responseTopic.replace("request", "response");
  client.publish(responseTopic.c_str(), payload);
}
// Hàm cập nhật trạng thái GPIO
void set_gpio_status(int pin, boolean enabled) {
  if (pin == LED1) {
    digitalWrite(LED1, enabled ? HIGH : LOW);
    ledState[0] = enabled;
  } else if (pin == LED2) {
    digitalWrite(LED2, enabled ? HIGH : LOW);
    ledState[1] = enabled;
  }
}

// Hàm thử kết nối lại MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", TOKEN, NULL)) {
      Serial.println("connected");
      client.subscribe(topic);    // Đăng ký nhận thông điệp từ ThingsBoard
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
