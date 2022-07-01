#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SdFat.h>                // SD card & FAT filesystem
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader.h> // Funzione per la lettura dell'immagine

#define USE_SD_CARD

#define TFT_CS   D8               // Pin digitale CS Display TFT
#define TFT_DC   D4               // Pin digitale DC Display TFT

#define SD_CS D2                  // Pin digitale CS SD-Card

#if defined(USE_SD_CARD)
  SdFat SD;                       // File system SD Card
  Adafruit_ImageReader reader(SD);    // oggetto da creare per la lettura
#else
  // SPI o QSPI flash filesystem
  #if defined(__SAMD51__) || defined(NRF52840_XXAA)
    Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS,
      PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
  #else
    #if (SPI_INTERFACES_COUNT == 1)
      Adafruit_FlashTransport_SPI flashTransport(SS, &SPI);
    #else
      Adafruit_FlashTransport_SPI flashTransport(SS1, &SPI1);
    #endif
  #endif
  Adafruit_SPIFlash flash(&flashTransport);
  FatFileSystem filesys;
  Adafruit_ImageReader reader(filesys);
#endif

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

Adafruit_Image img;
int32_t width  = 0, height = 0;

void setup(void) {

  ImageReturnCode stat; // Stato dalle funzioni di lettura delle immagini

  Serial.begin(9600);

  tft.begin();         // Avvio il display

  Serial.print(F("Initializing filesystem..."));

  #if defined(USE_SD_CARD)
  //La scheda SD è piuttosto semplice, una sola chiamata...
  if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) {
    Serial.println(F("SD begin() failed"));
    for(;;); // Errore fatale, non continuare
  }
#else
  // Il flash SPI o QSPI richiede due passaggi, uno per accedere alla stessa memoria flash
  // il secondo per accedere al file system della memoria
  if(!flash.begin()) {
    Serial.println(F("flash begin() failed"));
    for(;;);
  }
  if(!filesys.begin(&flash)) {
    Serial.println(F("filesys begin() failed"));
    for(;;);
  }
#endif
  Serial.println(F("OK!"));
  
  tft.setRotation(2);           // Ruoto il display
  tft.fillScreen(ILI9341_BLUE); // Coloro di blu il display

  delay(2000);
  
tft.fillScreen(0);        // Pulisco lo schermo
}

void loop() {

reader.drawBMP("/01.bmp", tft, 0, 0);         // Leggo l'immagine BMP
delay (1000);
img.draw(tft,240,320);                        // Scrivo l'immagine BMP con risoluzione 240x320
delay(3000);

reader.drawBMP("/02.bmp", tft, 0, 0);
delay (1000);
img.draw(tft,240,320);
delay(3000);

reader.drawBMP("/03.bmp", tft, 0, 0);
delay (1000);
img.draw(tft,240,320);
delay(3000);

reader.drawBMP("/04.bmp", tft, 0, 0);
delay (1000);
img.draw(tft,240,320);
delay(3000);
}
