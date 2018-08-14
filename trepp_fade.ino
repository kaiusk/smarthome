#include <SparkFun_Tlc5940.h>
#include <tlc_fades.h>

#define sensorLight_PIN A5                       // Light sensor  Do not change!!!
#define sensorBottom_PIN A1                      // Bottom sensor Do not change!!!                     
#define sensorUpper_PIN A2                       // Upper sensor  Do not change!!!
boolean sensorUpperActive;
boolean sensorBottomActive;
TLC_CHANNEL_TYPE channel;

void setup() {
  Tlc.init();
  pinMode(sensorBottom_PIN, INPUT);
  pinMode(sensorUpper_PIN, INPUT);
  pinMode(sensorLight_PIN, INPUT);
  Serial.begin(9600);
}



void loop() {
    uint32_t startMillis = 0; 
    
    if (tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2) {
        for (channel = 0; channel < 16; channel++) {
            if (!tlc_isFading(channel)) {
                startMillis = millis() + (channel * 200); // mitu ms hiljem alustab järgmine aste
                tlc_addFade(channel, 0, 4095, startMillis, startMillis + 500); // mitu ms kestab ühe aste fade
            }
        }
    }
    tlc_updateFades();
    //delay(10000);
    //Tlc.init(0);
}

