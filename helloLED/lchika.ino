#include <M5Stack.h>

#define LED_PIN 2
#define DAC 26

void setup() {
    M5.begin();
    pinMode(LED_PIN, OUTPUT);
}

int led = HIGH;

void papa() {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
}

void ziwa() {
    for (int i = 0; i < 256; i+= 10) {
        dacWrite(DAC, i);
        delay(100);
    }
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) {
        led = HIGH;
    }
    if (M5.BtnB.wasPressed()) {
        led = LOW;
    }
    if (M5.BtnC.wasPressed()) {
        led = (led == HIGH) ? LOW : HIGH;
    }
    digitalWrite(LED_PIN, led);
    delay(50);
}