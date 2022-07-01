#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Font_Data.h"
#include "RTClib.h"
#include <Wire.h>

RTC_DS3231 rtc;
DateTime now;

int  dd,mm,yyyy;
int  h, m, s;

#define MAX_DEVICES 4
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

//Pin NodeMCU ESP8266
#define CLK_PIN   D5 
#define DATA_PIN  D7
#define CS_PIN    D8


MD_Parola P = MD_Parola(HARDWARE_TYPE,CS_PIN, MAX_DEVICES);

#define SPEED_TIME 55 
#define PAUSE_TIME 0  

#define MAX_MESG  20

char szTime[9];    
char szMesg[MAX_MESG+1] = "";

uint8_t degC[] = { 6, 3, 3, 56, 68, 68, 68 }; 
uint8_t degF[] = { 6, 3, 3, 124, 20, 20, 4 };

char *mon2str(uint8_t mon, char *psz, uint8_t len)


{
  static const __FlashStringHelper* str[] =
  {
    F("Gen"), F("Feb"), F("Mar"), F("Apr"),
    F("Mag"), F("Giu"), F("Lug"), F("Ago"),
    F("Set"), F("Ott"), F("Nov"), F("Dic")
  };

  strncpy_P(psz, (const char PROGMEM *)str[mon-1], len);
  psz[len] = '\0';

  return(psz);
}

char *dow2str(uint8_t code, char *psz, uint8_t len)
{
  static const __FlashStringHelper*  str[] =
  {
  F("Domenica"), F("Lunedi"), F("Martedi"),
  F("Mercoledi"), F("Giovedi"), F("Venerdi"),
  F("Sabato"), F("Domenica")
  };

  strncpy_P(psz, (const char PROGMEM *)str[code-1], len);
  psz[len] = '\0';

  return(psz);
}
void getTime(char *psz, bool f = true)
{
  s = now.second();
  m = now.minute();
  h = now.hour();
    sprintf(psz, "%02d%c%02d", h, (f ? '.' : ' '), m);
 
 
}

void getDate(char *psz)
{
   char  szBuf[10];
    
   dd=now.day();
   mm=now.month(); 
   yyyy=now.year();
   sprintf(psz, "%d %s %04d",dd , mon2str(mm, szBuf, sizeof(szBuf)-1),(yyyy));
}

void setup(void)
{
  rtc.begin();
  P.begin(2);
  P.setInvert(false);

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2021, 11, 14, 12, 40, 0));
  
  P.setZone(0,  MAX_DEVICES-4, MAX_DEVICES-1);
  
  P.setZone(1, MAX_DEVICES-4, MAX_DEVICES-1);
  P.displayZoneText(1, szTime, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);

  P.displayZoneText(0, szMesg, PA_CENTER, SPEED_TIME, 0,PA_PRINT , PA_NO_EFFECT);

  P.addChar('$', degC);
  P.addChar('&', degF);

}

void loop(void)
{
  static uint32_t lastTime = 0; 
  static uint8_t  display = 0;  
  static bool flasher = false;

   now = rtc.now();

  P.displayAnimate();

   if (P.getZoneStatus(0))
  {
    switch (display)
    {
    case 0:    // Temperatura C
      P.setPause(0,1000);
      P.setTextEffect(0, PA_SCROLL_UP, PA_SCROLL_LEFT);
      display++;    
      dtostrf(rtc.getTemperature(), 3, 1, szMesg);
      strcat(szMesg, "$");
    

        break;

      case 1: // Temperatura F
        P.setTextEffect(0, PA_SCROLL_DOWN, PA_SCROLL_LEFT);
        display++;
        dtostrf((1.8 *rtc.getTemperature() )+32, 3, 1, szMesg);
        strcat(szMesg, "&");

        break;

      case 2: // Orario
     
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
      
      case 3: // Giorno della settimana
       
        P.setFont(0,nullptr);
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        dow2str(now.dayOfTheWeek()+1, szMesg, MAX_MESG);

       //dow2str(5, szMesg, MAX_MESG);
        break;
        case 4: // Calendario 
        P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        getDate(szMesg);
        break;
        case 5: // Messaggio
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
