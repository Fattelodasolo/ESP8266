#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define TFT_CS D0
#define TFT_DC D8
#define TFT_RST -1

#define TS_CS D3

XPT2046_Touchscreen ts(TS_CS);

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
 
const char* ssid = "nome-rete";
const char* password = "password";

bool state1 = 0;
bool touch1 = 0;
bool state2 = 0;
bool touch2 = 0;
bool state3 = 0;
bool touch3 = 0;
bool state4 = 0;
bool touch4 = 0;
bool state5 = 0;
bool touch5 = 0;

void setup () {
 
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3);
  
  WiFi.begin(ssid, password);

  Serial.println("In attesa di connessione");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }

  Serial.println("Connesso!");
  delay(500);
 
  ts.begin();
  ts.setRotation(1);
  Serial.println("Touch inizializzato!");
  delay(500);
  tft.fillScreen(ILI9341_BLACK);
  Home();


 }
 
void loop() {

if (ts.touched()) {
    TS_Point p = ts.getPoint();
    Serial.print("x = ");
    Serial.print(p.x);
    Serial.print("/ty = ");
    Serial.print(p.y);
    Serial.print("/tz = ");
    Serial.println(p.z);
    
  
    if (p.x > 665 && p.x < 1465 && p.y > 2650 && p.y < 3560) {
        state1 = 0;
        touch1 = !touch1;      
        }
     
    if (p.x > 1770 && p.x < 2550 && p.y > 2710 && p.y < 3560) {
        state2 = 0;
        touch2 = !touch2;      
        }

    if (p.x > 2860 && p.x < 3580 && p.y > 2550 && p.y < 3560) {
        state3 = 0;
        touch3 = !touch3;      
        }    
    
    if (p.x > 1130 && p.x < 1990 && p.y > 520 && p.y < 1510) {
        state4 = 0;
        touch4 = !touch4;      
        }

    if (p.x > 2240 && p.x < 3070 && p.y > 520 && p.y < 1420) {
        state5 = 0;
        touch5 = !touch5;      
        }
    }

// RL01
  if (state1 == 0 && touch1 == 0) {
    tft.fillRoundRect(15, 11, 88, 78, 5, ILI9341_RED);
    tft.setCursor(43, 42);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R01");
    state1 = 1;
    rl1_off();
    delay(200);
  }

  if (state1 == 0 && touch1 == 1) {
    tft.fillRoundRect(15, 11, 88, 78, 5, ILI9341_GREEN);
    tft.setCursor(43, 42);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R01");
    state1 = 1;
    rl1_on();
    delay(200);
  }
// RL02
  if (state2 == 0 && touch2 == 1) {
    tft.fillRoundRect(115, 11, 88, 78, 5, ILI9341_RED);
    tft.setCursor(143, 42);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R02");
    state2 = 1;
    rl2_off();
    delay(200);
  }

  if (state2 == 0 && touch2 == 0) {
    tft.fillRoundRect(115, 11, 88, 78, 5, ILI9341_GREEN);
    tft.setCursor(143, 42);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R02");
    state2 = 1;
    rl2_on();
    delay(200);
  }

// RL03
  if (state3 == 0 && touch3 == 1) {
    tft.fillRoundRect(215, 11, 88, 78, 5, ILI9341_RED);
    tft.setCursor(243, 42);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R03");
    state3 = 1;
    rl3_off();
    delay(200);
  }

  if (state3 == 0 && touch3 == 0) {
    tft.fillRoundRect(215, 11, 88, 78, 5, ILI9341_GREEN);
    tft.setCursor(243, 42);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R03");
    state3 = 1;
    rl3_on();
    delay(200);
  }

  //RL04
  if (state4 == 0 && touch4 == 0) {
    tft.fillRoundRect(61, 146, 88, 78, 5, ILI9341_RED);
    tft.setCursor(88, 175);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R04");
    state4 = 1;
    rl4_off();
    delay(200);
  }

  if (state4 == 0 && touch4 == 1) {
    tft.fillRoundRect(61, 146, 88, 78, 5, ILI9341_GREEN);
    tft.setCursor(88, 175);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R04");
    state4 = 1;
    rl4_on();
    delay(200);
  }

  // RL05
  if (state5 == 0 && touch5 == 0) {
    tft.fillRoundRect(161, 146, 88, 78, 5, ILI9341_RED);
    tft.setCursor(188, 175);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R05");
    state5 = 1;
    rl5_off();
    delay(200);
  }

  if (state5 == 0 && touch5 == 1) {
    tft.fillRoundRect(161, 146, 88, 78, 5, ILI9341_GREEN);
    tft.setCursor(188, 175);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("R05");
    state5 = 1;
    rl5_on();
    delay(200);
  }
}

void Home(){
  tft.drawRoundRect(0, 0, 320, 240, 5, ILI9341_WHITE);
  tft.drawRoundRect(14, 10, 90, 80, 5, ILI9341_WHITE);
  tft.drawRoundRect(114, 10, 90, 80, 5, ILI9341_WHITE);
  tft.drawRoundRect(214, 10, 90, 80, 5, ILI9341_WHITE);
  tft.drawRoundRect(60, 145, 90, 80, 5, ILI9341_WHITE);
  tft.drawRoundRect(160, 145, 90, 80, 5, ILI9341_WHITE);

  tft.setCursor(55, 100);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Multisocket EPS32");
  tft.setCursor(60, 120);
  tft.println("Controller v.1.0");

  
}

void rl1_on(){
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay01/on");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl1_off(){
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay01/off");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl2_on(){
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http; 
 
    http.begin("http://192.168.1.153/Relay02/on");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl2_off(){
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay02/off");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl3_on(){
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay03/on");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl3_off(){
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay03/off");
    int httpCode = http.GET();
 
     
    http.end();

    }
}


void rl4_on(){
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay04/on");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl4_off(){
  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay04/off");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl5_on(){
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay05/on");
    int httpCode = http.GET();
 
     
    http.end();

    }
}

void rl5_off(){
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;
 
    http.begin("http://192.168.1.153/Relay05/off"); 
    int httpCode = http.GET();
 
     
    http.end();

    }
}
