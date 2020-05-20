#include <M5Stack.h>
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

const int R = 266;
const int Xt = 286;
const int Yt = 225;
const int Xh = 34;
const int Yh = 225;

void drawLineByAngle(int16_t x,
                     int16_t y, 
                     int16_t start,
                     int16_t length,
                     int16_t angle,
                     int thick,
                     uint16_t color);

void drawScale(){
    //Temp
    M5.Lcd.setCursor(35, 10);
    M5.Lcd.print("temp('C)");
    for (int i = -10; i <= 40; i++) {
        int l1 = (i % 10) ? 5 : 10;
        drawLineByAngle(Xt, Yt, R - l1, l1, map(i, -10, 40, 270, (270 + 50)), 1, BLACK);

        if (i % 20 == 0) {
            int a = map(i, -10, 40, 0, 50);
            M5.Lcd.setCursor(Xt - R * cos(radians(a)) - 15,
                             220 - R * sin(radians(a)));
            M5.Lcd.print(i);
        }
    }
    //Humid


}

void setup(){
    M5.begin();
    Serial.begin(115200);
    while(! Serial);

    if (! sensor.begin()) {
        Serial.println("Did no find si7021");
        while(true);
    }

    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLACK, WHITE);

    drawScale();
}

void loop(){

}



