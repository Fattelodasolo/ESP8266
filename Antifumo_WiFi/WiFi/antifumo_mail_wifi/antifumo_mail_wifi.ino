//   Programma realizzato da Letterio Bavastrelli e rilasciato con GNU GPL V.3
//   Rilevamento Fumo con inoltro e-mail di avviso via WiFi ESP8266 12-F su account Virgilio
//   Copyright (C) 2017  Letterio Bavastrelli

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.

// Contact me: letteriobavastrelli@gmail.com

// Visit my YT Channel: https://www.youtube.com/Reshitoze

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "NomeReteWifi"; //Nome della rete WiFi
const char* password = "PasswordWifi"; //Password della rete WiFi

// Impostazioni di rete
byte mac[] = { 0x18, 0xFE, 0x34, 0xA1 ,0x5C, 0x44 }; //Indirizzo MAC della ESP8266-12F 
IPAddress ip( 192, 168, 1, 17 );    
IPAddress gateway( 192, 168, 1, 1 );
IPAddress subnet( 255, 255, 255, 0 );

// Login data:
 String UserName64 = "UsernameBase64";
 String Password64 = "PasswordBase64==";
  char server[] = "out.virgilio.it"; // Virgilio Server SMTP

 
// SMTP server VIRGILIO
String ServerName = "virgilio.it";
 
// Mail data:
String Sender = "mittente@virgilio.it";       // Indirizzo email mittente
String Recipient = "destinatario@virgilio.it";    // Indirizzo dove recapitare la mail
String Subject = "Sensore Rilevamento Fumo";         // Oggetto email
String Body = "Rilevato fumo nel bagno uomini secondo piano. Intervenire!";   // Testo email


 int wait = 1000;
 String ServerResponse="";
 WiFiClient client;

 
void setup()
{
  Serial.begin(9600);
}

void loop()
{
 // Se ci sono bytes in arrivo dal sever, leggili e stampali
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  
 int fumo = analogRead(A0);
  
  if (fumo < 100); // Se non c'è fumo, allora non inviare email
      
  else {
    Connection();
    SMTP_email_command();
    }
     // Se c'è fumo avvia funzione SMTP_email_command()
}

void Connection(){
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
if (client.connect(server, 25)) {
   Serial.println("WiFi connesso");  
   Serial.println("Indirizzo IP: ");
   Serial.println(WiFi.localIP());
   Serial.println("Connesione al Server...");
   client.println();
   Serial.println("");
  }
  }

void SMTP_email_command(void) // Invio email con SMTP
{
     SendMsg("EHLO " + ServerName);
     SendMsg("AUTH LOGIN ");
     SendMsg(UserName64);
     SendMsg(Password64);
     SendMsg("MAIL From:<" + Sender +">");
     SendMsg("RCPT To:<" + Recipient + ">");
     SendMsg("DATA");
     SendMsg("To: " + Recipient); 
     SendMsg("From: " + Sender); 

     SendMsg("Subject: "+ Subject);
     SendMsg(""); 
     SendMsg(Body);
     SendMsg(""); 
     SendMsg(".");
     SendMsg("QUIT");
     client.println();
     client.stop();
}

void GetResponse() {
    if (client.available()) {
         char c = client.read();
         while (client.available()) { // Store command char by char.
           ServerResponse +=c;
           c = client.read();
         }
    Serial.println("<<<" + ServerResponse);
    ServerResponse="";
  }
 }
 
void SendMsg(String m) {
   client.println(m);
   Serial.println(">>>" + m);
   delay(wait);
   GetResponse();
 }
