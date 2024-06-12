#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "NTPClient.h"
#include "WiFiUdp.h"

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

#include "sun.c"

#define TFT_CS D0
#define TFT_DC D8
#define TFT_RST -1

#define TS_CS D3

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

const char* ssid = "CASA_WIRELESS";
const char* password = "sodarktheconofman";
const char* mqtt_server = "192.168.1.190";
const int mqtt_server_port = 1883;
const char* mqttUser = "homeassistant";
const char* mqttPassword = "que1lunguichaiGio2liebuut7ou4iechoh3Iexe0oolee3Kavoh9phuv2xeiyai";

WiFiClient espClient;
PubSubClient client(espClient);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

float prevPower = -1.0;
float prevEnergyD = -1.0;
float prevEnergyM = -1.0;
float prevCo2 = -1.0;

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3);

  delay(1000);
  
  Serial.println();
  Serial.print("Connessione a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connessione WiFi stabilita");
  Serial.println("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);

 tft.fillScreen(ILI9341_BLACK);
 tft.drawRoundRect(0, 0, 320, 240, 5, ILI9341_WHITE);

 tft.drawBitmap(40, 10, gImage_sun, 80, 80, ILI9341_YELLOW);

 tft.setCursor(70, 150);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);
    tft.println("W");
 tft.setCursor(20, 200);
    tft.setTextColor(ILI9341_CYAN);
    tft.setTextSize(2);
    tft.println("Produzione");
 tft.setCursor(20, 215);
    tft.setTextColor(ILI9341_CYAN);
    tft.setTextSize(2);
    tft.println("Istantanea");

 tft.drawRect(160, 8, 1, 226, ILI9341_WHITE);
 tft.drawRect(160, 80, 156, 1, ILI9341_WHITE);
 tft.drawRect(160, 160, 156, 1, ILI9341_WHITE);

 tft.setCursor(170, 10);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.println("Energia Oggi"); 

 tft.setCursor(170, 90);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(2);
    tft.println("Energia Mese");

  tft.setCursor(170, 170);
    tft.setTextColor(0x8410);
    tft.setTextSize(2);
    tft.println("CO2");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Info impianto [");
  Serial.print(topic);
  Serial.print("] ");

  // Copia il payload in una stringa
  String payloadStr;
  for (unsigned int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }
  Serial.println(payloadStr);

  // Estrai i valori specifici dal payload
  float power = 0.0, energyD = 0.0, energyM = 0.0, co2 = 0.0;

  int powerIndex = payloadStr.indexOf("Power ");
  int energyDIndex = payloadStr.indexOf("EnergyD ");
  int energyMIndex = payloadStr.indexOf("EnergyM ");
  int co2Index = payloadStr.indexOf("CO2 ");

  if (powerIndex != -1) {
    power = payloadStr.substring(powerIndex + 6, payloadStr.indexOf(" ", powerIndex + 6)).toFloat();
  }
  if (energyDIndex != -1) {
    energyD = payloadStr.substring(energyDIndex + 8, payloadStr.indexOf(" ", energyDIndex + 8)).toFloat();
  }
  if (energyMIndex != -1) {
    energyM = payloadStr.substring(energyMIndex + 8, payloadStr.indexOf(" ", energyMIndex + 8)).toFloat();
  }
  if (co2Index != -1) {
    co2 = payloadStr.substring(co2Index + 4).toFloat();
  }

  // Stampa i valori estratti
  Serial.print("Power: ");
  Serial.println(power);
  Serial.print("EnergyD: ");
  Serial.println(energyD);
  Serial.print("EnergyM: ");
  Serial.println(energyM);
  Serial.print("CO2: ");
  Serial.println(co2);

  // Controlla se i valori sono cambiati rispetto ai valori precedenti
  bool powerChanged = (power != prevPower);
  bool energyDChanged = (energyD != prevEnergyD);
  bool energyMChanged = (energyM != prevEnergyM);
  bool co2Changed = (co2 != prevCo2);

  // Aggiorna solo se i valori sono cambiati
  if (powerChanged || energyDChanged || energyMChanged || co2Changed) {
    // Aggiorna valori precedenti
    prevPower = power;
    prevEnergyD = energyD;
    prevEnergyM = energyM;
    prevCo2 = co2;

    // Pulisci solo l'area del testo che cambia
    if (powerChanged) {
      tft.fillRect(10, 100, 150, 40, ILI9341_BLACK); // Pulisci l'area del testo di Power
      // Scrivi il nuovo valore di Power
      tft.setCursor(10, 100);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(4);
      tft.println(power);
    }
    if (energyDChanged) {
      tft.fillRect(170, 45, 120, 20, ILI9341_BLACK); // Pulisci l'area del testo di EnergyD
      // Scrivi il nuovo valore di EnergyD
      tft.setCursor(170, 45);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(2);
      tft.print(energyD);
      tft.println(" kWh");
    }
    if (energyMChanged) {
      tft.fillRect(170, 125, 120, 20, ILI9341_BLACK); // Pulisci l'area del testo di EnergyM
      // Scrivi il nuovo valore di EnergyM
      tft.setCursor(170, 125);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(2);
      tft.print(energyM);
      tft.println(" kWh");
    }
    if (co2Changed) {
      tft.fillRect(170, 200, 120, 20, ILI9341_BLACK); // Pulisci l'area del testo di CO2
      // Scrivi il nuovo valore di CO2
      tft.setCursor(170, 200);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(2);
      tft.print(co2);
      tft.println(" kg");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.subscribe("home/lolin");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  timeClient.update();
}
