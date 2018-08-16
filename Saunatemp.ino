#include <SparkFun_Tlc5940.h>

TLC_CHANNEL_TYPE channel;

int arvud[10][7] = {
    // a,b,b,d,e,f,g
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
};

void setup() {
    Tlc.init();
    Serial.begin(9600);
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
        int heledus = 4095 * a[i];
        channel = i + 8 * led;
        Tlc.set(channel, heledus);
    }
    Tlc.update();
}


void loop() {
    for (int i=0; i<10; i++) {
        dec_to_lcd(0, i); // esimene nr on 2
        dec_to_lcd(1, i+1); // teine nr on 8
        delay(2000);
    }
}

