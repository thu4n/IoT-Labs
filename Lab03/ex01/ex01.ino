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

        function incrementScore() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', '/increment-score', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    updateScore(xhr.responseText);
                }
            };
            xhr.send();
        }
    </script>
</head>
<body>
    <h1></h1>
    <h1 id='score'>Score: 0</h1>
    <a href="/b1"><button>Button 1</button></a><br>
    <a href="/b2"><button>Button 2</button></a><br>
    <a href="/b3"><button>Button 3</button></a><br>
</body>
</html>

)=====";

const char Gameover_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Guest the num</title>
</head>
<body>
    <h1>Game over!</h1>
    <a href="/"><button>Try again!</button></a><br>
</body>
)=====";

// LED pin (built-in LED by default)
#define LED LED_BUILTIN
#define DELAY_LED 200

// WiFi credentials (replace with your network details)
const char* ssid = "UiTiOt-E3.1";
const char* password = "UiTiOtAP";

int ledNum;
int score = 0;

// Web server object
ESP8266WebServer server(80);
const int ledPins[] = {D3, D4, D5, D6, D7};

// Webpage handlers
void handleRoot() {
  Serial.println("You called root page");
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleB1() {
  Serial.println("You press Button 1");
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleB2() {
  Serial.println("You press Button 2");
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleB3() {
  Serial.println("You press Button 3");
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleGameover() {
  Serial.println("Game over");
  String html = Gameover_page;
  server.send(200, "text/html", html);
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

void getCase() {
  int cs = ledNum % 3;
  switch (cs)
  {
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  }
}

// Setup function
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
  server.on("/b1", handleB1);
  server.on("/b2", handleB2);
  server.on("/b3", handleB3);
  server.on("/over", handleGameover);
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  server.handleClient();
  randomLED();
}