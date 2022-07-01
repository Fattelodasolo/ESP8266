#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <YoutubeApi.h>
#include <ArduinoJson.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

#include "YT.h"

#define TFT_CS D0
#define TFT_DC D8
#define TFT_RST -1

#define API_KEY "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define CHANNEL_ID "xxxxxxxxxxxxxxxxxxxxxxxx"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

char ssid[] = "nome-rete";
char password[] = "password";

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long timeBetweenRequests = 60000;
unsigned long nextRunTime;


void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
 
  client.setInsecure();
  api._debug = true;

  tft.fillScreen(ILI9341_WHITE);
  tft.drawBitmap( 100, 10, YT, 120, 90,  ILI9341_RED);

}

void loop() {
  if (millis() > nextRunTime)  {
    if(api.getChannelStatistics(CHANNEL_ID)){
      Serial.print("Iscritti: ");
      Serial.println(api.channelStats.subscriberCount);
      Serial.print("Visualizzazioni: ");
      Serial.println(api.channelStats.viewCount);

    tft.setCursor(70, 125);
    tft.setTextColor(ILI9341_BLACK,ILI9341_WHITE);
    tft.setTextSize(8);
    tft.println(api.channelStats.subscriberCount);
    tft.setTextSize(2);
    tft.setCursor(10, 215);
    tft.print("Views: ");
    tft.println(api.channelStats.viewCount);
    
    }
    nextRunTime = millis() + timeBetweenRequests;
  }
}
