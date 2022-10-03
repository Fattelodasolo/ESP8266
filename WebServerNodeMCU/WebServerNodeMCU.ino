#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "nome-rete-wifi";
const char* password = "pw-wifi";
ESP8266WebServer server(80);

String stringa = "Hello World!";

void setup() {
  Serial.begin (9600);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connettiti a: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    if (MDNS.begin("nodemcu")) {
    Serial.print("NodeMCU online: ");
    Serial.println("http://nodemcu.local/");

     }

  server.on("/", caricamento);
  server.begin();
}

void loop() {
 server.handleClient();
 MDNS.update();

}

void caricamento(){

server.send(200, "text/plain","NodeMCU V3 ti da il benvenuto!");            // stampa un semplice testo
//server.send(200, "text/html","<h1>NodeMCU:" + stringa + "</h1>");         // stampa una pagina HTML
  
}
