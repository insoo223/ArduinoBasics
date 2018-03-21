#define LCD_CS A3    
#define LCD_CD A2    
#define LCD_WR A1   
#define LCD_RD A0    
// you can also just connect RESET to the arduino RESET pin
#define LCD_RESET A4
//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:
// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF

#include "TFTLCD.h"
#include <dht.h>

#define dht_dpin 10 //no ; here. Set equal to channel sensor is on

dht DHT;

TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup(void) 
{
  tft.reset();
  tft.initDisplay();
  tft.fillScreen(BLACK);

  pinMode(10, INPUT);
} // setup

void loop(void) 
{
  DHT.read11(dht_dpin);

  tft.setTextColor(WHITE);
  tft.setTextSize(2);

  tft.setCursor(10, 0);
  tft.print("Humidity: ");
  tft.print(round(DHT.humidity)); 
  tft.print(" %");

  tft.setCursor(10, 20);
  tft.print("Temp: ");
  tft.print(round(DHT.temperature)); 
  tft.print((char)223);
  tft.print("C");
 
  delay(1000);
  
} // loop


