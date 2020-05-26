#include <M5Stack.h>

#define P_PIN 35

void setup() {
    M5.begin();
    pinMode(P_PIN, INPUT);

    M5.Lcd.setTextSize(4);
}

void loop() {
    int e = analogRead(P_PIN);

    M5.Lcd.setCursor(80, 100);
    M5.Lcd.print(e, 1);

    delay(1000);
}