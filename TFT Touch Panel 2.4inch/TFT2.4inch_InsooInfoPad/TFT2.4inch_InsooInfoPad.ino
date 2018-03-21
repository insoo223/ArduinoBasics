#include <TFTLCD.h>
#include <TouchScreen.h>

#define showInfo_X 5   // information display coordinate, x
#define showInfo_Y 150   // information display coordinate, y
#define showInfo_deltaY 40   // information display coordinate, delta

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
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 600);
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 150);

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

void testtext(uint16_t);

void setup(void) {
  int i, k;
  float modifierX, modifierY;

  Serial.begin(9600);
  Serial.println("Number Pad!");

  tft.reset();
  tft.initDisplay(); 
  tft.fillScreen(BLACK);
  
  //Number pad
  for (i=0; i<3; i++)
    for (k=0; k<1; k++)
    {
      tft.drawRect(BOXSIZE*i, BOXSIZE*k, BOXSIZE, BOXSIZE, WHITE);
      if (k < 3)
        switch (i)
        {
          case 0:
            modifierX = 15; modifierY = 10;
            tft.drawChar(BOXSIZE*i+modifierX, BOXSIZE*k+modifierY, (char)(49 + (k*3)+i), YELLOW, 6); 
            break;
          case 1:
            modifierX = 1.25; modifierY = 10;
            tft.drawChar(BOXSIZE*i*modifierX, BOXSIZE*k+modifierY, (char)(49 + (k*3)+i), YELLOW, 6); 
            break;
          case 2:
            modifierX = 1.1; modifierY = 10;
            tft.drawChar(BOXSIZE*i*modifierX, BOXSIZE*k+modifierY, (char)(49 + (k*3)+i), YELLOW, 6); 
            break;
        }   
          
      else
        if (i == 0)
          tft.drawChar(BOXSIZE*i+15, BOXSIZE*k*1.05, (char)(42), YELLOW, 6); // *
        else if (i == 1)
          tft.drawChar(BOXSIZE*i*1.25, BOXSIZE*k*1.05, (char)(48), YELLOW, 6); // 0
        else
          tft.drawChar(BOXSIZE*i*1.1, BOXSIZE*k*1.05, (char)(35), YELLOW, 6); // #
    } // for i, k
    //tft.drawString(BOXSIZE*0, BOXSIZE*4 + 10, "Insoo's Num Pad", WHITE, 2); 
    tft.drawString(BOXSIZE*0, BOXSIZE + 10, "Insoo's Info Pad", WHITE, 2); 
    tft.drawString(BOXSIZE*0, BOXSIZE + 30, "Press a number...", WHITE, 2); 
    tft.drawString(BOXSIZE*0, BOXSIZE + 50, "Coded on: ", WHITE, 2); 
    tft.drawString(BOXSIZE*0, BOXSIZE + 70, __DATE__, WHITE, 2); 
    tft.drawString(BOXSIZE*0, BOXSIZE + 90, __TIME__, WHITE, 2); 
} // setup

char pressedChar;
void loop()
{
  int i;
  
  Point p = ts.getPoint();
  
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  
  if ((p.x > 200) && (p.x < 240))
  {
    if (p.y > 240)
      pressedChar = '1';
    else if (p.y > 160)
      pressedChar = '2';
    else if (p.y > 80)
      pressedChar = '3';
    else
      pressedChar = '?';
  } // if ((p.x > 200) && (p.x < 240))
  
  // Check printed icons on LCD 
  if ((p.x > -10) && (p.x < 15))
  {
    if (p.y < 30)
    {
      Serial.println("Home");
      tft.fillScreen(BLACK);
      tft.setCursor(10, 10);
      tft.setTextColor(WHITE);
      tft.setTextSize(3);
      tft.println("Hello World!");
      //tft.drawString(20, 10, "Home", YELLOW, 3);
      //tft.drawVerticalLine (0, 15, 100, YELLOW);
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

  // Don't know why put these statement as of Dec11,2014    
  // To be tested
  // As of March 12, 2018, found out why these three output commands work.
  // Having these three commands set, read touch panel enabled.
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(YM, OUTPUT);

  switch (pressedChar)
  { 
    case '1':
    case '2':
    case '3':
      Serial.println(pressedChar);
      tft.drawChar(BOXSIZE*3.5, BOXSIZE*1, pressedChar, YELLOW, 6); 
      delay(500);
      tft.drawChar(BOXSIZE*3.5, BOXSIZE*1, pressedChar, BLACK, 6); 
      delay(500);
      showInsooInfo();
      break;
  }

} // loop

void showInsooInfo()
{
  switch (pressedChar)
  {
    case '1'://email
      tft.fillScreen(BLACK);
      //delay(500);
      tft.drawString(showInfo_X,showInfo_Y,"insoo@", WHITE, 4);
      tft.drawString(showInfo_X,showInfo_Y+showInfo_deltaY,"hotmail", WHITE, 4);
      tft.drawString(showInfo_X,showInfo_Y+(2*showInfo_deltaY),".com", WHITE, 4);
      break;
    case '2'://mobile
      tft.fillScreen(BLACK);
      //delay(500);
      tft.drawString(showInfo_X,showInfo_Y,"010-8530-8908", WHITE, 3);
      break;
    case '3'://office tel
      tft.fillScreen(BLACK);
      //delay(500);
      tft.drawString(showInfo_X,showInfo_Y,"070-8330-9000", WHITE, 3);
      break;
  }  
}//showInsooInfo


