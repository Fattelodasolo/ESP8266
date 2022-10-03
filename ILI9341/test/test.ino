#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "reshitoze.c"

#define TFT_CS D0 
#define TFT_DC D8 
#define TFT_RST -1
#define TS_CS D3


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);
  Serial.println("TFT START!");

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);

}

void loop() {

tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_RED);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_WHITE);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_GREEN);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_ORANGE);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_MAGENTA);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_YELLOW);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_BLUE);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_DARKCYAN);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_NAVY);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_MAROON);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_PURPLE);
delay(500);
tft.drawBitmap(0, 0, gImage_reshitoze, 240, 320, ILI9341_LIGHTGREY);
delay(500);

}
