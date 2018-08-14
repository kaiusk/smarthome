#include <SparkFun_Tlc5940.h>
#include <tlc_fades.h>

#define sensorLight_PIN A5                       // Light sensor  Do not change!!!
#define sensorBottom_PIN A1                      // Bottom sensor Do not change!!!                     
#define sensorUpper_PIN A2                       // Upper sensor  Do not change!!!
boolean sensorUpperActive;
boolean sensorBottomActive;
TLC_CHANNEL_TYPE channel;
uint32_t startMillis; 
int yhe_astme_aeg = 500;
int koik_polevad = 10000;
int astmete_vaheline_aeg = 200;

void setup() {
  Tlc.init();
  pinMode(sensorBottom_PIN, INPUT);
  pinMode(sensorUpper_PIN, INPUT);
  pinMode(sensorLight_PIN, INPUT);
  Serial.begin(9600);
}

void setChannel(TLC_CHANNEL_TYPE ch) {
    if (!tlc_isFading(ch)) {
        startMillis = millis() + (ch * astmete_vaheline_aeg); // mitu ms hiljem alustab järgmine aste
        // fadein
        tlc_addFade(ch, 0, 4095, startMillis, startMillis + yhe_astme_aeg); // mitu ms kestab ühe aste fade
        // fadeout
        tlc_addFade(ch, 4095, 0, startMillis + koik_polevad, startMillis + koik_polevad + yhe_astme_aeg ); // mitu ms kestab ühe aste fade
    }
}

void liiguYles() {
    if (tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2 && sensorBottomActive) {
        for (channel = 0; channel < 16; channel++) {
            setChannel(channel);
        }
    }
    tlc_updateFades();
}

void liiguAlla() {
    if (tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2 && sensorUpperActive) {
        for (channel = 15; channel < 1; channel--) {
            setChannel(channel);
        }
    }
    tlc_updateFades();
}

void loop() {
    liiguYles();
    delay(10000);
    liiguAlla();
    delay(10000);
}
