#include <SparkFun_Tlc5940.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

TLC_CHANNEL_TYPE channel;

int arvud[10] = {
  B1111110, // 0
  B0110000, // 1
  B1101101, // 2
  B1111001, // 3
  B0110011, // 4
  B1011011, // 5
  B1011111, // 6
  B1110000, // 7
  B1111111, // 8
  B1111011  // 9
};

void setup() {
    sensors.begin();
    Tlc.init();
    //Serial.begin(9600);
}


/*
 * nr on 0..9 ja led on 0,1
 */
void dec_to_lcd(int led, int nr) {
    if (nr>9)
        nr = 0;
    if (nr<0)
        nr = 9;
    
    int a = arvud[nr];
    for (int i = 0; i < 8; i++) {
        int heledus = 4095 * bitRead(a, i);
        channel = i + 8 * led;
        Tlc.set(channel, heledus);
    }
    Tlc.update();
}


void loop() {
    sensors.requestTemperatures();
    int tempC = sensors.getTempCByIndex(0);
    int tmp = int(tempC*10);
    
    dec_to_lcd(1, (int(tmp)%100)/10);
    dec_to_lcd(0, (int(tmp)%100)%10);
    
    delay(5000);
    
    /*for (int i=0; i<10; i++) {
        dec_to_lcd(0, i); 
        dec_to_lcd(1, i+1); 
        delay(2000);
    }*/
}
