#include <SparkFun_Tlc5940.h>
//#include <tlc_animations.h>
//#include <tlc_config.h>
//#include <tlc_fades.h>
//#include <tlc_progmem_utils.h>
//#include <tlc_servos.h>
//#include <tlc_shifts.h>

#define sensorLight_PIN A5                       // Light sensor  Do not change!!!
#define sensorBottom_PIN A1                      // Bottom sensor Do not change!!!                     
#define sensorUpper_PIN A2                       // Upper sensor  Do not change!!!
unsigned int maxBrightness = 512;                // Here you set the number of brightness levels.!!
boolean sensorUpperActive;
boolean sensorBottomActive;
int numberOfstairs=16;                           // Setup Number of Your stairs.
int pause=30000;                                 // Setup delay ON/OFF  Adjust!!! 
byte faidoutSpeed=5;                             // How fast to fadeout     Adjust!!!
byte faidinSpeed=5;                              // How fast to fadein      Adjust!!!
int val;

void setup() {
  Tlc.init();
  pinMode(sensorBottom_PIN, INPUT);
  pinMode(sensorUpper_PIN, INPUT);
  pinMode(sensorLight_PIN, INPUT);
  Serial.begin(9600);
}



void loop() {
  val = analogRead(5);                               //Checking light level 
  if (val <= 1000) {                               // Adjust photocell cencivity. (val<10 dark.....val>800 bright..)    !!!!!!!!
    BottomTriggerFire();                           //Checking bottom sensor
    UpperTrigerFire();                             //Checking upper sensor
    switchONOFFfromdown();                         //Stairs on/off from down to up
    switchONOFFfromUp();                           //Stairs on/off from up to down
  }
}

void BottomTriggerFire() {
  if (analogRead (sensorBottom_PIN) >= 550 ) {      //Dependof the sensor type, if 0 when triggered ,than change the comparison to opposite value
    sensorBottomActive = true;
  }
}

void UpperTrigerFire() {
  if (analogRead(sensorUpper_PIN) >= 550) {
    sensorUpperActive = true;
  }
}

void SetLed(int nr, int heledus) {
  if (nr>=0 && nr<=numberOfstairs) {
    if (heledus>4096) {
      heledus = 4096;
    }
    Tlc.set(nr, heledus);
  }
}

void switchONOFFfromdown() {
  if (sensorBottomActive==true && sensorUpperActive==false){
    int min_heledus = 0;
    
    for(int i=0; i<numberOfstairs; i++){
        Serial.print(i);
        if (i>0) {
          min_heledus = 384;
        }
        for(int a=min_heledus; a<maxBrightness; a++){
            SetLed(i,   a*8);
            SetLed(i+1, a*6);
            SetLed(i+2, a*4);
            SetLed(i+3, a*2);
            Tlc.update();
            delay(faidoutSpeed);
        }
    }
      
    delay(pause); 

        
    for(int i=0; i<numberOfstairs; i++){
        //Serial.print(i);
        if (i>0) {
          maxBrightness = 128;
        }
        for(int a=maxBrightness;a>=0;a--){
            SetLed(i,   a*8);
            SetLed(i+1, (a + 128)*8);
            SetLed(i+2, (a + 256)*8);
            SetLed(i+3, (a + 384)*8);
            Tlc.update();
            delay(faidinSpeed);
       }
    }
    sensorBottomActive = false ;  
  }
}
         
void switchONOFFfromUp () {
  int min_heledus = 0;
  if ( sensorUpperActive==true && sensorBottomActive==false) {
    for(int i=numberOfstairs-1; i>=0; i--){
      Serial.print(i);
      if (i<(numberOfstairs-1)) {
        min_heledus = 384;
      }
      for(int a=min_heledus; a<maxBrightness; a++){
          SetLed(i,   a*8);
          SetLed(i-1, a*6);
          SetLed(i-2, a*4);
          SetLed(i-3, a*2);
          Tlc.update();
          delay(faidoutSpeed);
      }
    }
    
    delay(pause); 

          
    for(int i=numberOfstairs-1; i>=0; i--){
      //Serial.print(i);
      if (i<(numberOfstairs-1)) {
          maxBrightness = 128;
        }
      for(int a=maxBrightness;a>=0;a--){
        SetLed(i,   a*8);
        SetLed(i-1, (a + 128)*8);
        SetLed(i-2, (a + 256)*8);
        SetLed(i-3, (a + 384)*8);
        Tlc.update();
        delay(faidinSpeed);
      }
    }
    sensorUpperActive= false ;  
  }
  
} 
