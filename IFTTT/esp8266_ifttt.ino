#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <EEPROM.h>

const char* ssid = "NOME-WIFI";
const char* password = "passwordWiFi";

const char* host = "maker.ifttt.com";
const int httpsPort = 443;

const char fingerprint[] PROGMEM = "24 8E 25 32 85 E5 E8 64 2C C9 94 41 1A B2 FB 84 36 2B DD 09";

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(2000);
  EEPROM.begin(512);

  while(!Serial) {}
  
  Serial.println("Sono sveglio");

  Connection();
 
  ESP.deepSleep(0); 
}

void Connection(){

int state = EEPROM.read(0);

WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connessa");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (state == 0){

      luce_on();

      state = 1;
      EEPROM.write(0, state);
      EEPROM.commit();
  }

   else {
      luce_off();
      state = 0;
      EEPROM.write(0, state);
      EEPROM.commit();
    }   
    
  }

void luce_off(){
  // Connessione TLS
  WiFiClientSecure client;
  Serial.print("connessione a ");
  Serial.println(host);

  Serial.printf("Utilizza fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connessione fallita");
    return;
  }

  String url = "/trigger/luce_off/with/key/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  Serial.print("richiesta URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("richiesta inviata");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("ricevuta");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI fallito!");
  } else {
    Serial.println("esp8266/Arduino CI avvenuto");
  }
  Serial.println("risposta Host:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("chiudi connessione");

}
  

void luce_on(){
// Connessione TLS
  WiFiClientSecure client;
  Serial.print("connessione a ");
  Serial.println(host);

  Serial.printf("Utilizza fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connessione fallita");
    return;
  }

  String url = "/trigger/luce_on/with/key/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("richiesta inviata");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("ricevuta");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI fallito!");
  } else {
    Serial.println("esp8266/Arduino CI avvenuto");
  }
  Serial.println("risposta Host:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("chiudi connessione");
  
}

void loop() {

}
