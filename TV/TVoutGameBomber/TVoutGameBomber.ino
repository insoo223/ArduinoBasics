    /********************************************
     * Arduino Bomber                           *
     *                                          *
     * Roberto Melzi - 12 maggio 2015           *
     *                                          *
     ********************************************/
     
    #include <TVout.h>
    #include <fontALL.h>
    #define BUTTON_PIN 1  
    #define WHEEL_PIN 0 
    #define IN_GAME 0   //in game state
    #define IN_MENU 1   //in menu state
    #define GAME_OVER 2 //game over state
     
    TVout TV;
    unsigned char x,y;
    boolean buttonStatus = 0;
    int wheelPosition = 0;
    int BomberX = 0; 
    float bombX = 3.0;
    float bombY = 10.0; 
    float bombV0 = 1.2;  
    float bombX0 = TV.hres()/2; 
    float bombY0 = 0; 
    float aereoX = 3.0;
    float aereoY = 10.0;
    float Vaereo = 1.0; 
    int ricarica = 0; 
    int aereoColpito = 0;
    int bombaColpita = 1; 
    int t = 0; 
    int score = 40; 
    int level = 0; 
    int frame = 0;
    int state = IN_MENU;
     
    void processInputs() {
      wheelPosition = analogRead(WHEEL_PIN);
      buttonStatus = (analogRead(BUTTON_PIN) > 512); 
    }
     
    void drawGameScreen() {
      TV.clear_screen();
      //draw plane ------------------------------------------
      TV.draw_line(aereoX - 2,aereoY,aereoX + 3,aereoY, 1);
      TV.draw_line(aereoX,aereoY + 2,aereoX,aereoY - 3, 1);
      if(Vaereo > 0) {
         TV.draw_line(aereoX - 2,aereoY - 2,aereoX - 2,aereoY, 1);
         TV.draw_line(aereoX - 2,aereoY-1,aereoX + 2,aereoY-1, 1);
      }
      if(Vaereo < 0) {
         TV.draw_line(aereoX + 2,aereoY - 2,aereoX + 2,aereoY, 1);
         TV.draw_line(aereoX - 1,aereoY-1,aereoX + 3,aereoY-1, 1);
      }
      //draw bomb --------------------------------------------
      TV.draw_line(bombX-1,bombY-1,bombX+2,bombY-1,1);
      TV.draw_line(bombX-1,bombY-2,bombX+2,bombY-2,1);
      TV.set_pixel(bombX, bombY-3, 1);
      TV.set_pixel(bombX-1, bombY-4, 1);
      TV.set_pixel(bombX+1, bombY-4, 1);
      TV.set_pixel(bombX, bombY, 1);
      // draw score line ----------------------------------------
      TV.set_pixel(TV.hres()-100,0,1); 
      TV.draw_line(TV.hres(),0,TV.hres()-score,0,1);  
      //draw ground ---------------------------------------------
      TV.draw_line(TV.hres(),TV.vres()-1,1,TV.vres()-1, 1); 
      //draw bombard --------------------------------------------
      BomberX = ((wheelPosition / 8) * (TV.hres() - 11))/ 128 + 6;
      TV.draw_line(BomberX,TV.vres()-6,BomberX,TV.vres()-9,1);
      TV.draw_line(BomberX-2,TV.vres()-5,BomberX+3,TV.vres()-5,1);
      TV.draw_line(BomberX-5,TV.vres()-4,BomberX+6,TV.vres()-4,1);
      TV.draw_line(BomberX-5,TV.vres()-3,BomberX+6,TV.vres()-3,1);
      TV.draw_line(BomberX-5,TV.vres()-2,BomberX+6,TV.vres()-2,1);
      // draw shot ------------------------------------------------
      if ( buttonStatus == 1 && ricarica == 0) {
         TV.draw_line(BomberX,TV.vres()-9,BomberX,0,1);
         score += -1; 
         ricarica = 1; 
       }
   }

   void drawMenu() {
      x = 0;
      y = 0;
      char volX = 1;
      char volY = 1;
      TV.clear_screen();
      TV.select_font(font8x8);
      TV.print(5, 5, "Arduino Bomb");
      TV.print(5, 20, "JinGo 38th!");
      
      TV.select_font(font6x8);
      //TV.print(22, 55, "Press Button");
      //TV.print(50, 65, "To Start");
      TV.print(15, 55, "Button To Start");
      //TV.print(50, 65, "To Start");
      
      //TV.print(15, 35, "Press Button");
      //TV.print(22, 45, "To Start");
      delay(1000);
          
      while(!buttonStatus) {
        processInputs();
        //TV.delay_frame(3);
        TV.delay_frame(1); // insoo modified
        if(x + volX < 1 || x + volX > TV.hres() - 1) {volX = -volX; TV.tone(146, 100);}
        if(y + volY < 1 || y + volY > TV.vres() - 1) {volY = -volY; TV.tone(146, 100);}
        if(TV.get_pixel(x + volX, y + volY)) {
          TV.set_pixel(x + volX, y + volY, 0);
         
          if(TV.get_pixel(x + volX, y - volY) == 0) {
            volY = -volY;
            TV.tone(220, 100); 
          }
          else if(TV.get_pixel(x - volX, y + volY) == 0) {
            volX = -volX;
            TV.tone(220, 100); 
          }
          else {
            volX = -volX;
            volY = -volY;
            TV.tone(220, 100);  
          }
        }
        TV.set_pixel(x, y, 0);
        x += volX;
        y += volY;
        TV.set_pixel(x, y, 1);
      }
      buttonStatus = 0; 
      delay(100);
      TV.select_font(font6x8);
      state = IN_GAME;
    }
     
    void setup()  {
      Serial.begin(9600);
      x=0;
      y=0;
      //TV.begin(_PAL);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
      TV.begin(_NTSC); // insoo modifed on 2017.4.4
    }
     
    void loop() {
      processInputs();
     
      if(state == IN_MENU) {
        drawMenu();
      }
      if(state == IN_GAME) {
        if(frame % 2 == 0) { //every third frame - game speed  
        // plane position --------------------------------------------
        aereoX += Vaereo;
       
        if (ricarica == 1) {  // this is exectuted just after a shot ------
           if (BomberX > aereoX - 2 - level && BomberX < aereoX + 3 + level) { // plane is hit ------------------
              aereoX = -10; 
              score += 8;
              TV.tone(110, 200);
              delay(50); 
            }
            if (BomberX > (bombX - 2 )&& BomberX < (bombX + 2)) { // bomb is hit ----------------
              bombX0 = 2*TV.hres();
              bombY0 = -100.; 
              bombV0 = 0;  
              score += 8; 
              TV.tone(165, 200);
              delay(50); 
            }
         }
        // plane has escaped ------------------------------------------------------
        if(aereoX >= TV.hres() || aereoX <= 0 ) {
          score += -4 - 2*level; 
           Vaereo = random(200)/100.0 + 0.5 + level; 
           aereoY = random(TV.vres()*2/3*100)/100.0 + 2; 
           if(random(1000) > 500)
             {aereoX = 10;} 
           else {
             aereoX = TV.hres()-10; 
             Vaereo = -Vaereo; 
             }
         }
        // bomb position and trajectory ----------------------------------------
          bombX = bombX0 + bombV0*t;            
          bombY = bombY0 + t*t/(48 - 18*level);
          if(bombY >= TV.vres() || bombX < 0 || bombX > TV.hres()){
            if(bombX >= BomberX - 5 && bombX < BomberX + 6){
               TV.print(50, 35, "Hit!"); 
               score += -30; 
               TV.tone(440, 200); 
               TV.delay(180);
               TV.tone(220, 200);
               TV.delay(180);
               TV.tone(110, 200); 
               TV.delay(180);
               TV.tone(55, 200);
               TV.delay(280);
            }
            bombY0 = aereoY + 4;
            bombX0 = aereoX;
            bombV0 = Vaereo - level + random(-100,100)/100.; 
            t = 0;
          }
          else
         {t = t + 1;}
        // check the shot ---------------------------------------------
        if(ricarica > 0 ) {
           ricarica += 1; 
           if (ricarica > 5) {ricarica = 0;}
        }
        // check score state -----------------------------------------
        if(score < 0) {state = GAME_OVER;}
        if (score > 100) {
          score = 100;
          if(level == 0){
            TV.tone(440, 120);
            delay(100); 
            TV.tone(880, 120);
            delay(100); 
            level = 1; 
          }
        }
      }
      
      drawGameScreen();
      }
      if(state == GAME_OVER) {
        drawGameScreen();       
        TV.select_font(font8x8);
        TV.print(29,25,"GAME");
        TV.print(68,25,"OVER");
        TV.tone(440, 200); 
        TV.delay(180);
        TV.tone(220, 200);
        TV.delay(180);
        TV.tone(110, 200); 
        TV.delay(180);
        TV.tone(55, 200);
        TV.delay(180);
        buttonStatus = 0; 
        level = 0; 
        
        while(!buttonStatus) {
          processInputs();
          delay(100);
        }
        TV.select_font(font8x8); //reset the font
        score = 40; 
        buttonStatus = 0; 
        delay(100);
        state = IN_MENU;
      }

      TV.delay_frame(1);
      if(++frame == 60) frame = 0; //increment and/or reset frame counter
    }


