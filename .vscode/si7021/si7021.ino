#include <M5Stack.h>
#include "Adafruit_Si7021.h"
#include "Seeed_BMP280.h"
#include <Wire.h>

Adafruit_Si7021 sensor = Adafruit_Si7021();
BMP280 bmp280;

void setup() {
    M5.begin();

    M5.Lcd.print("hello");

    if (! sensor.begin()) {
        Serial.println("Did no find si7021");
        while(true);
    }

    if (! bmp280.init()) {
        Serial.println("Device not connected or broken");
        while(true);
    }

    M5.Lcd.setTextSize(3);
}

void loop() {
    float temp = sensor.readTemperature();
    float humid = sensor.readHumidity();

    float bmp280temp = bmp280.getTemperature();
    uint32_t pressure = bmp280.getPressure();
    float altitude = bmp280.calcAltitude(pressure);

    M5.Lcd.setCursor(40, 30);
    M5.Lcd.printf("Temp: %5.1f'C", temp);

    M5.Lcd.setCursor(40, 70);
    M5.Lcd.printf("Humid: %5.1f%%", humid);

    M5.Lcd.setCursor(40, 110);
    M5.Lcd.printf("BTemp: %5.1f'C", bmp280temp);

    M5.Lcd.setCursor(40, 150);
    M5.Lcd.printf("BPress: %dhPa", pressure / 100);

    M5.Lcd.setCursor(40, 190);
    M5.Lcd.printf("BAlti: %5.2fm", altitude);

    delay(1000);
}