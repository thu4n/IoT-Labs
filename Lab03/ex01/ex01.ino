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
        let isClicked = false;
        let scr = 0;

        function updateScore(score) {
            document.getElementById('score').innerHTML = 'Score: ' + score;
        }

        function handleButtonClick(buttonId) {
          var xhr = new XMLHttpRequest();
          var url = "/" + buttonId; // Construct URL dynamically based on buttonId
          xhr.open('GET', url, true);
          xhr.onreadystatechange = function() {
            if (xhr.readyState == 4 && xhr.status == 200) {
              isClicked = true;
              scr = scr + parseInt(xhr.responseText);
              updateScore(scr);
            }
          };
          xhr.send();
        }

        function checkTime() {
          if (!isClicked) {
            scr--;
          }
          updateScore(scr);
          isClicked = false;
        }

        setInterval(checkTime, 2000);
    </script>
</head>
<body>
    <h1></h1>
    <h1 id='score'>Score: --</h1>
    <button onclick='handleButtonClick(1)'>Button 1</button>
    <button onclick='handleButtonClick(2)'>Button 2</button>
    <button onclick='handleButtonClick(3)'>Button 3</button>
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
  server.on("/1", HTTP_GET, handleB1);
  server.on("/2", HTTP_GET, handleB2);
  server.on("/3", HTTP_GET, handleB3);
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  server.handleClient();
  randomLED();
}

void checkNum(int num) {
  int score = 0;
  if (ledNum % 3 == num)
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

// Webpage handlers
void handleRoot() {
  Serial.println("You called root page");
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleB1() {
  Serial.println("You press Button 1: ");
  checkNum(0);
}

void handleB2() {
  Serial.println("You press Button 2: ");
  checkNum(1);
}

void handleB3() {
  Serial.println("You press Button 3: ");
  checkNum(2);
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