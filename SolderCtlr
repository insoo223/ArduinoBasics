
/*
  SolderCtlr
  Turns on and off an ACPwrSwitch of power relay to control the temperature of solder.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an ACPwrSwitch connected on most Arduino boards.
// give it a name:
int ACPwrSwitch = 13;
int InitHeatingLED = 11;
int SafeHeatingLED = 9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ACPwrSwitch, OUTPUT);    
  pinMode(InitHeatingLED, OUTPUT);      
  pinMode(SafeHeatingLED, OUTPUT);      

  // turn the ACPwrSwitch On for 2 min
  // for heating the solder to get sufficient temp at the beginning
  digitalWrite(ACPwrSwitch, HIGH);   
  digitalWrite(InitHeatingLED, HIGH);   
  digitalWrite(SafeHeatingLED, LOW);   
  // Initial heating for 120 seconds
  delay(120000);               
  digitalWrite(InitHeatingLED, LOW);
  //it's time to safe heating, i.e. periodic heating  
  digitalWrite(SafeHeatingLED, HIGH);   
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(ACPwrSwitch, LOW);   
  delay(10000);               // pwr off 10 seconds
  digitalWrite(ACPwrSwitch, HIGH);  
  delay(10000);               // pwr on 10 seconds
}
