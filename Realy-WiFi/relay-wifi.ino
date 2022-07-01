#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char* ssid = "nome_wifi";
const char* password = "password";

WiFiServer server(80);

void setup() {
  
  pinMode(D2,OUTPUT);   // Direzione del pin D2
  digitalWrite(D2,LOW); // Disponiamo come spento il relè

  Serial.begin(9600);
  Serial.print("Connessione alla rete WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  Serial.print("Connessione");
  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  Serial.println("Connessione WiFi avvenuta!");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP() );
    
  server.begin();

  // Crea un nome con cui trovare facilmente la scheda in rete
  if (MDNS.begin("relay")) {
    Serial.print("RELAY online: ");
    Serial.println("http://relay.local/");

     }

  
}

void loop() {

    MDNS.update();  // Aggiorna il MDNS

    // Verifica che sia connesso un client
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(10);
  }

   // Legge la richiesta
  String quero = client.readStringUntil('\r');
  Serial.println(quero);
  client.flush();

  // Elabora la richiesta  
  int stato = LOW;
  if (quero.indexOf("/RELAY=ON") != -1)  {
    digitalWrite(D2, HIGH);
    stato = HIGH;
  }
  if (quero.indexOf("/RELAY=OFF") != -1)  {
    digitalWrite(D2, LOW);
    stato = LOW;
  }
 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("<h1>WI-FI RELAY: </h1>");
 
  // se il valore è LOW...
  if(stato == LOW) {
    client.print("<h1 style='color:red'>OFF</h1>");
    client.println("<a href=\"/RELAY=ON\"\"><button style='height:100px;width:200px;font-size:2vw'>Attiva </button></a>");   // il relè è spento e crea il pulsante Attiva
    
  } 

  else {
    client.print("<h1 style='color:green'>ON</h1>");
    client.println("<a href=\"/RELAY=OFF\"\"><button style='height:100px;width:200px;font-size:2vw'>Disattiva </button></a><br />"); // il relè è acceso e crea il pulsante Disattiva
  }
 
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnesso.");
  Serial.println("");


  
}
