#include "TFTLCD.h"
#include "TouchScreen.h"

//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

/*
#define YP 6  // must be an analog pin, use "An" notation!
#define XM 7  // must be an analog pin, use "An" notation!
#define YM A2   // can be a digital pin
#define XP A1   // can be a digital pin
*/

//#define TS_MINX 150
#define TS_MINX 110
//#define TS_MINY 120
#define TS_MINY 200
#define TS_MAXX 920
//#define TS_MAXY 940
#define TS_MAXY 890

#define MINPRESSURE 10
#define MAXPRESSURE 1000


// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 150);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
// optional
#define LCD_RESET A4

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF


TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 60
#define PENRADIUS 3

int oldcolor, currentcolor;

void setup(void) {
  int i, k;
  
  Serial.begin(9600);
  Serial.println("String Test!");
  tft.reset();
  
  tft.initDisplay(); 
  tft.fillScreen(BLACK);
  
//Horizontal tiles
  //k=0;
  for (i=0; i<3; i++)
    for (k=0; k<4; k++)
    {
      tft.drawRect(BOXSIZE*i, BOXSIZE*k, BOXSIZE, BOXSIZE, WHITE);
      if (k < 3)
        tft.drawChar(BOXSIZE*i, BOXSIZE*k, (char)(49 + (k*3)+i), YELLOW, 6); 
      else
        if (i=0)
          tft.drawChar(BOXSIZE*i, BOXSIZE*k, (char)(42), YELLOW, 6); 
        else if (i=1)
          tft.drawChar(BOXSIZE*i, BOXSIZE*k, (char)(48), YELLOW, 6); 
        else
          tft.drawChar(BOXSIZE*i, BOXSIZE*k, (char)(35), YELLOW, 6); 
      
    }


  
 //pinMode(13, OUTPUT);
} // setup

void loop()
{
  int i;
  //digitalWrite(13, HIGH);
  Point p = ts.getPoint();
  //digitalWrite(13, LOW);

  /*
  Serial.print("Pressure p.z: ");
  Serial.println(p.z);
  Serial.print("X-coord p.x: ");
  Serial.println(p.x);
  Serial.print("Y-coord p.y: ");
  Serial.println(p.y);
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  Serial.print("Calibrated X-coord mapped p.x: ");
  Serial.println(p.x);
  Serial.print("Calibrated Y-coord mapped p.y: ");
  Serial.println(p.y);
  */
  
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    if ((p.x > 200) && (p.x < 240))
    {
      if (p.y > 240)
      {
        Serial.println("1");
        //tft.drawString(20, 10, "Home", YELLOW, 3);
        //tft.drawVerticalLine (0, 15, 100, YELLOW);
      }
      else if (p.y > 160)
        Serial.println("2");
      else if (p.y > 80)
        Serial.println("3");
      else
        Serial.println("1?");
    } // if ((p.x > 200) && (p.x < 240))
    else if (p.x > 160)
    {
      if (p.y > 240)
      {
        Serial.println("4");
        //tft.drawString(20, 10, "Home", YELLOW, 3);
        //tft.drawVerticalLine (0, 15, 100, YELLOW);
      }
      else if (p.y > 160)
        Serial.println("5");
      else if (p.y > 80)
        Serial.println("6");
      else
        Serial.println("2?");
    } // else if (p.x > 160)
    else if (p.x > 120)
    {
      if (p.y > 240)
        Serial.println("7");
      else if (p.y > 160)
        Serial.println("8");
      else if (p.y > 80)
        Serial.println("9");
      else
        Serial.println("3?");
    } // else if (p.x > 120)
    else if (p.x > 80)
    {
      if (p.y > 240)
        Serial.println("*");
      else if (p.y > 160)
        Serial.println("0");
      else if (p.y > 80)
        Serial.println("#");
      else
        Serial.println("4?");
    } // else if (p.x > 80)
  
  /*
  for (i=0; i<3; i++)
  {
    tft.drawString(BOXSIZE*i, BOXSIZE*i, "Home", YELLOW, 3); 
    tft.fillRect(BOXSIZE*2, BOXSIZE*i, BOXSIZE, BOXSIZE, GREEN);
    delay(500);
  }
  */
  
  /*
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  Serial.print("Calibrated X-coord mapped p.x: ");
  Serial.println(p.x);
  Serial.print("Calibrated Y-coord mapped p.y: ");
  Serial.println(p.y);
  */
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(YM, OUTPUT);
  delay(1000);

} // loop
