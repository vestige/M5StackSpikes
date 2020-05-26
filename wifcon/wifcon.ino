#include <M5Stack.h>
#include <WiFi.h>

const char * ssid = "---";
const char * pass = "---";

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);
    
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print('.');
    }

    M5.Lcd.print("\r\nWiFi conncted\r\nIP Address: ");
    M5.Lcd.print(WiFi.localIP());    
}

void loop() {
}
