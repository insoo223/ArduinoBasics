#include "TFTLCD.h"
#include "TouchScreen.h"

//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

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
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

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

#define BOXSIZE 40
#define PENRADIUS 3

int oldcolor, currentcolor;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Coordinate Test!");
  tft.reset();
  
  tft.initDisplay(); 
  tft.fillScreen(BLACK);
  
//Horizontal tiles
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);

 tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
 currentcolor = RED;
 
 pinMode(13, OUTPUT);
} // setup

void loop()
{
  digitalWrite(13, HIGH);
  Point p = ts.getPoint();
  digitalWrite(13, LOW);
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
  if ((p.x > -10) && (p.x < 15))
  {
    if (p.y < 30)
    {
      Serial.println("Home");
      tft.drawString(20, 10, "Home", YELLOW, 3);
      tft.drawVerticalLine (0, 15, 100, YELLOW);
    }
    else if (p.y < 100)
      Serial.println("Headphone");
    else if (p.y < 180)
      Serial.println("Mail");
    else if (p.y < 250)
      Serial.println("Disc");
    else if (p.y < 320)
      Serial.println("Address");
  } // if ((p.x > -10) && (p.x < 15))

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);
  delay(1000);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
/*
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

    
    if (p.y < (TS_MINY-5)) {
      Serial.println("erase");
     // press the bottom of the screen to erase 
      tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
      
    }
    // turn from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
Serial.println(p.x);
Serial.println(p.y);
    if (p.y < BOXSIZE) {
       oldcolor = currentcolor;
 
  
       if (p.x < BOXSIZE) { 
         currentcolor = RED; 
         tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
       } 
       else if (p.x < BOXSIZE*2) {
         currentcolor = YELLOW; 
         tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*3) {
         currentcolor = GREEN; 
         tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*4) {
         currentcolor = CYAN; 
         tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*5) {
         currentcolor = BLUE; 
         tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       else if (p.x < BOXSIZE*6) {
         currentcolor = MAGENTA; 
         tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE);
       }
       
       if (oldcolor != currentcolor) {
          if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
          if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
          if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
          if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
          if (oldcolor == BLUE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
          if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
       }
    }
    if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
      tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
  }
*/  
} // loop
