#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

#include "EmonLib.h"
EnergyMonitor emon1;

const char* ssid = "XXXXXXXX";
const char* password =  "xxxxxxxxx";
const char* mqtt_server = "xxx.xxx.xxx.xxx";
const int mqtt_server_port = 1883;
const char* mqttUser = "xxxxxxxxxx";
const char* mqttPassword = "xxxxxxxxxxxxxxxxxxxx";

WiFiClient wifiClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
PubSubClient mqttClient(wifiClient);

unsigned long time_now = 0;

float power, Irms, consumo;




void setup() {
Serial.begin(115200);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);


 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connessione al WiFi..");
  }
  Serial.print("Connesso alla rete WiFi");
  Serial.println(WiFi.localIP());
  
  mqttClient.setServer(mqtt_server, mqtt_server_port);

  emon1.current(A0, 10.0);

}

void loop() {


   if (!mqttClient.connected()) {
     connect();
   }
   mqttClient.loop();
   timeClient.update();

if(millis() > time_now + 3000){
Irms = emon1.calcIrms(1480);  // Calcola corrente
mqttClient.publish("sensor/amp", String(Irms).c_str());

power = Irms*230.00*0.8;  // Calcola Watt
mqttClient.publish("sensor/power", String(power).c_str());

consumo = (power/1000)*1;  // Calcola kWh
mqttClient.publish("sensor/consumo", String(consumo).c_str());

Serial.print(Irms);
Serial.println("A");
Serial.print(power);
Serial.println("Watt");
Serial.print(consumo);
Serial.println("kWh");

  time_now = millis(); 
  }

}


void connect() {
   while (!mqttClient.connected()) {
     Serial.print("Attendere connessione MQTT...");
     String mqttClientId = "";
     if (mqttClient.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
       Serial.println("connesso");
     } else {
       Serial.print("fallita, rc=");
       Serial.print(mqttClient.state());
      Serial.println(" tentativo tra 5 secondi");
       delay(5000);
     }
   }
 }
