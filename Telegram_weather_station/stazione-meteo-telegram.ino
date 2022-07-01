#include "CTBot.h"
#include <BME280I2C.h>
#include <Wire.h>

CTBot myBot;
BME280I2C bme;

#define WIFI_SSID "nome-wifi"
#define WIFI_PASSWORD "password"

#define BOT_TOKEN "XXXXXXXXX:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

int64_t CHAT_ID = xxxxxxxxxx;

float temp, hum, pres;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bme.begin();

  bme_sensor();


  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  myBot.wifiConnect(WIFI_SSID, WIFI_PASSWORD);
  myBot.setTelegramToken (BOT_TOKEN);

if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

   String data = "Ciao, la Temperatura è di " + String(temp) + "°C, la Pressione è di " + String(pres) + " Pa e l'Umidità è del " + String(hum) + "%";
  
   myBot.sendMessage(CHAT_ID, data);


  ESP.deepSleep(36e8);  

  }

void loop() {

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
