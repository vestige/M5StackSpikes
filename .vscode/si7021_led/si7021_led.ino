#include <M5Stack.h>
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

#define LED_PIN 2

int WBGlevel(float humid, float temp) {
    if (temp > (humid * (-12.0 / 70.0) + 40.0 + 36.0 / 7.0))
        return 3;

    if (temp > humid * (-13.0 / 80.0) + 25.0 + 130.0 / 8.0)
        return 2;

    if (temp > humid * (-3.0 / 20.0) + 37.0)
        return 1;
    
    return 0;
}

void setup() {
    M5.begin();

    pinMode(LED_PIN, OUTPUT);

    if (! sensor.begin()) {
        Serial.println("Did no find si7021");
        while(true);
    }

    M5.Lcd.setTextSize(3);
}

void loop() {
    float temp = sensor.readTemperature();
    float humid = sensor.readHumidity();

    M5.Lcd.setCursor(40, 80);
    M5.Lcd.printf("Temp: %5.1f'C", temp);
    M5.Lcd.setCursor(40, 140);
    M5.Lcd.printf("Humid: %5.1f%%", humid);

    if (WBGlevel(humid, temp) > 1) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
    delay(1000);
}