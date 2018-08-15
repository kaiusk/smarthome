#include <SparkFun_Tlc5940.h>
#include <tlc_fades.h>

#define sensorLight_PIN 1
#define sensorBottom_PIN 2
#define sensorUpper_PIN 3

boolean sensorUpperActive;
boolean sensorBottomActive;
boolean fadeActive;
TLC_CHANNEL_TYPE channel;
uint32_t startMillis; 
int oneLEDtime = 500;
int allLEDon = 10000;
int delayBetweenLED = 200;

void setup() {
    Tlc.init();
    pinMode(sensorBottom_PIN, INPUT);
    digitalWrite (sensorBottom_PIN, LOW);
    pinMode(sensorUpper_PIN, INPUT);
    digitalWrite (sensorUpper_PIN, LOW);
    pinMode(sensorLight_PIN, INPUT);
    //Serial.begin(9600);
}

void BottomTriggerFire() {
    if (digitalRead (sensorBottom_PIN) && !fadeActive) {      //Dependof the sensor type, if 0 when triggered ,than change the comparison to opposite value
        sensorBottomActive = true;
    }
}

void UpperTriggerFire() {
    if (digitalRead (sensorUpper_PIN) && !fadeActive) {      //Dependof the sensor type, if 0 when triggered ,than change the comparison to opposite value
        sensorUpperActive = true;
    }
}

void setChannel(TLC_CHANNEL_TYPE ch) {
    // fadein
    tlc_addFade(ch, 0, 4095, startMillis, startMillis + oneLEDtime); // mitu ms kestab ühe aste fade
    // fadeout
    tlc_addFade(ch, 4095, 0, startMillis + allLEDon, startMillis + allLEDon + oneLEDtime ); // mitu ms kestab ühe aste fade
}

void moveUp() {
    if (tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2 && sensorBottomActive) {
        for (channel = 0; channel < 16; channel++) {
            if (!tlc_isFading(ch)) {
                startMillis = millis() + (ch * delayBetweenLED); 
                setChannel(ch);
            }
        }
        sensorBottomActive = false;
    }
}

void moveDown() {
    if (tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2 && sensorUpperActive) {
        for (channel = 15; channel < 1; channel--) {
            if (!tlc_isFading(ch)) {
                startMillis = millis() + ((15 - ch) * delayBetweenLED);
                setChannel(ch);
            }
        }
        sensorUpperActive = false;        
    }
}

void loop() {
    if (digitalRead (sensorLight_PIN)) {        //Dependof the sensor type, if 0 when triggered ,than change the comparison to opposite value
        BottomTriggerFire();
        UpperTriggerFire();
        moveUp();
        moveDown();
    }
    fadeActive = tlc_updateFades();
}
