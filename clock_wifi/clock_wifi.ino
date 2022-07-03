#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "Font_Data.h"

const char *ssid     = "XXXXXXXXXXXXX";
const char *password = "xxxxxxxxxxxxxx";

const long utcOffsetInSeconds = 7200;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);

int  h, m, s;
int yy, mm, dd;

#define MAX_DEVICES 4
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

//Pin NodeMCU ESP8266
#define CLK_PIN   D5 
#define DATA_PIN  D7
#define CS_PIN    D8


MD_Parola P = MD_Parola(HARDWARE_TYPE,CS_PIN, MAX_DEVICES);

#define SPEED_TIME 55 
#define PAUSE_TIME 0  

#define MAX_MESG  30

char szTime[9];    
char szMesg[MAX_MESG+1] = "";

char daysOfTheWeek[7][12] = {"Domenica", "Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi", "Sabato"};

String months[12]={"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio", "Agostot", "Settembre", "Ottobre", "Novembre", "Dicembre"};

void getTime(char *psz, bool f = true){
  s = timeClient.getSeconds();
  m = timeClient.getMinutes();
  h = timeClient.getHours();
    sprintf(psz, "%02d%c%02d", h, (f ? '.' : ' '), m);
}

void getDate(char *psz){
   char  szBuf[10];
   time_t epochTime = timeClient.getEpochTime();
   struct tm *ptm = gmtime ((time_t *)&epochTime);

    dd = ptm->tm_mday;
    mm = ptm->tm_mon+1;
    String currentMonthName = months[mm-1];
    yy = ptm->tm_year+1900;

   sprintf(psz, "%d %s %04d", dd, currentMonthName, yy);
}

void setup(){
  Serial.begin(115200);

  timeClient.begin(); 

  P.begin(2);
  P.setInvert(false);
  
  P.setZone(0,  MAX_DEVICES-4, MAX_DEVICES-1);
  
  P.setZone(1, MAX_DEVICES-4, MAX_DEVICES-1);
  P.displayZoneText(1, szTime, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);

  P.displayZoneText(0, szMesg, PA_CENTER, SPEED_TIME, 0,PA_PRINT , PA_NO_EFFECT);

  Serial.println();
  Serial.println();
  Serial.print("Connessione a ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connesso");
  Serial.println("");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP()); 

}

void loop(){
  
    timeClient.update();

    P.displayAnimate();
      
    static uint32_t lastTime = 0; 
    static uint8_t  display = 0;  
    static bool flasher = false;

   if (P.getZoneStatus(0))
  {
    switch (display)
    {
    case 0:
      P.setPause(0,1000);
      P.setFont(0, numeric7Seg);
      P.setTextEffect(0, PA_PRINT, PA_NO_EFFECT);
      P.setPause(0,0);

      if (millis() - lastTime >= 1000)
        {
        lastTime = millis();
        getTime(szMesg, flasher);
        flasher = !flasher;
        }
      if(s==00&& s<=30){
        display++;
        P.setTextEffect(0,  PA_CLOSING, PA_GROW_DOWN);
        }             
    
    break;      
    case 1: // Giorno della settimana
     P.setFont(0,nullptr);
     P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
     display++;
     strcpy (szMesg, daysOfTheWeek[timeClient.getDay()]);

    break;
    case 2: // Calendario 
     P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
     display++;
     getDate(szMesg);
        
    break;
    case 3: // Messaggio
      P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      strcpy(szMesg, "www.fattelodasolo.it"); 
      display=0;
    break;
    default:  
    display = 0;
    break;
    }
     
    P.displayReset(0); //reset
    
  }
}
