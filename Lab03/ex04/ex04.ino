#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Daivjppro";
const char* password = "123456780";
const char* mqtt_server = "broker.mqtt-dashboard.com";

const int ledPin = D3;  // Chân kết nối đến đèn LED

WiFiClient espClient;
PubSubClient client(espClient);

const char* topicToSubscribe = "cl21/nhom2/led";

void setup_wifi() {
  delay(10);
  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Convert byte array to string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Check message content and control LED accordingly
  if (message.equals("1")) {
    digitalWrite(ledPin, HIGH);  // Bật đèn LED
    Serial.println("LED turned ON");
  } else if (message.equals("0")) {
    digitalWrite(ledPin, LOW);  // Tắt đèn LED
    Serial.println("LED turned OFF");
  } else {
    Serial.println("Invalid message");
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, subscribe to the topic
      client.subscribe(topicToSubscribe);
      Serial.print("Subscribed to: ");
      Serial.println(topicToSubscribe);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);  // Khai báo chân kết nối đèn LED là OUTPUT
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
