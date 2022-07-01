#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <BME280I2C.h>
#include <Wire.h>

#define WIFI_SSID "XXXXXXXXXXXXX"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxx"

#define BOT_TOKEN "XXXXXXXXX:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

#define CHAT_ID "xxxxxxxx"

BME280I2C bme;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

float temp, hum, pres;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  bme.begin();

  bme_sensor();
  Serial.println();

  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setTrustAnchors(&cert);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  configTime(0, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
  
  String data = "Ciao, la Temperatura è di " + String(temp) + "°C, la Pressione è di " + String(pres) + " Pa e l'Umidità è del " + String(hum) + "%";
  
   bot.sendMessage(CHAT_ID, data, "");

   ESP.deepSleep(36e8); 
}


void bme_sensor(){

  bme.read(pres, temp, hum);


  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println ("°C");

  Serial.print("Umidità: ");
  Serial.print (hum);
  Serial.println(" %");

  Serial.print("Pressione: ");
  Serial.print (pres);
  Serial.println (" Pa");
}

void loop() {

}
