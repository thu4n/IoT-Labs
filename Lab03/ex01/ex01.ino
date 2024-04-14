#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Webpage content stored in program memory
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Guest the num</title>
    <script>
        function updateScore(score) {
            document.getElementById('score').innerHTML = 'Score: ' + score;
        }

        function checkB1() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/b1', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    updateScore(xhr.responseText);
                }
            };
            xhr.send();
        }

        function checkB2() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/b2', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    updateScore(xhr.responseText);
                }
            };
            xhr.send();
        }

        function checkB3() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/b3', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    updateScore(xhr.responseText);
                }
            };
            xhr.send();
        }

        function checkTime() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/time', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    updateScore(xhr.responseText);
                }
            };
            xhr.send();
        }

        setInterval(checkTime, 2000);
    </script>
</head>
<body>
    <h1></h1>
    <h1 id='score'>Score: 0</h1>
    <button onclick='checkB1()'>Button 1</button>
    <button onclick='checkB2()'>Button 2</button>
    <button onclick='checkB3()'>Button 3</button>
</body>
</html>

)=====";

// LED pin (built-in LED by default)
#define LED LED_BUILTIN
#define DELAY_LED 200

// WiFi credentials (replace with your network details)
const char* ssid = "";
const char* password = "";

int ledNum = 0;
int score = 0;
int start = 0;
bool isClicked = false;

// Web server object
ESP8266WebServer server(80);
const int ledPins[] = {D3, D4, D5, D6, D7};

void setup() {
  Serial.begin(115200);
  srand(time(NULL));
  WiFi.begin(ssid, password);
  Serial.println("");

  for (int i = 0; i < 5; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  startLed();
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/b1", HTTP_GET, handleB1);
  server.on("/b2", HTTP_GET, handleB2);
  server.on("/b3", HTTP_GET, handleB3);
  server.on("/time", HTTP_GET, handleTime);
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  isClicked = false;
  server.handleClient();
  randomLED();
}

// Webpage handlers
void handleRoot() {
  Serial.println("You called root page");
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleB1() {
  isClicked = true;
  Serial.println("You press Button 1: ");
  if (ledNum % 3 == 0)
  {
    Serial.print("Correct");
    score++;
  } else {
    Serial.print("Incorrect");
    score--;
  }
  Serial.println("");
  String html = MAIN_page;
  server.send(200, "text/html", String(score));
}

void handleB2() {
  isClicked = true;
  Serial.println("You press Button 2: ");
  if (ledNum % 3 == 1)
  {
    Serial.print("Correct");
    score++;
  } else {
    Serial.print("Incorrect");
    score--;
  }
  Serial.println("");
  server.send(200, "text/html", String(score));
}

void handleB3() {
  isClicked = true;
  Serial.println("You press Button 3: ");
  if (ledNum % 3 == 2)
  {
    Serial.print("Correct");
    score++;
  } else {
    Serial.print("Incorrect");
    score--;
  }
  Serial.println("");
  String html = MAIN_page;
  server.send(200, "text/html", String(score));
}

void handleTime() {
  Serial.println("Time out");
  if (!isClicked)
  {
    score--;
  }
  server.send(200, "text/html", String(score));
}

void startLed() {
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(DELAY_LED);
  }
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(ledPins[i], LOW);
    delay(DELAY_LED);
  }
  for (int i = 4; i >=0 ; i--)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(DELAY_LED);
  }
  for (int i = 4; i >=0 ; i--)
  {
    digitalWrite(ledPins[i], LOW);
    delay(DELAY_LED);
  }
}

void randomLED() {
  ledNum = random(1, 6);
  Serial.println("Right button: ");
  Serial.print(ledNum % 3 + 1);
  Serial.println("");
  start = millis();
  int seed = random(1, 6);
  randomSeed(ledNum, seed);
}

void randomSeed(int numled, int seed) {
  int seed1[5] = {2, 4, 1, 3, 0};
  int seed2[5] = {4, 2, 1, 3, 0};
  int seed3[5] = {3, 2, 1, 0 ,4};
  int seed4[5] = {0, 2, 1, 3 ,4};
  int seed5[5] = {1, 4, 2, 3 ,0};

  switch (seed)
  {
  case 1:
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed1[i]], HIGH);
    }
    delay(2000);
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed1[i]], LOW);
    }
    break;
  case 2:
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed2[i]], HIGH);
    }
    delay(2000);
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed2[i]], LOW);
    }
    break;
  case 3:
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed3[i]], HIGH);
    }
    delay(2000);
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed3[i]], LOW);
    }
    break;
  case 4:
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed4[i]], HIGH);
    }
    delay(2000);
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed4[i]], LOW);
    }
    break;
  case 5:
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed5[i]], HIGH);
    }
    delay(2000);
    for (int i = 0; i < numled; i++)
    {
      digitalWrite(ledPins[seed5[i]], LOW);
    }
    break;
  }
}