#include <M5Stack.h>

void setup() {
  M5.begin();

  M5.Lcd.fillCircle(155, 160, 10, WHITE);
  M5.Lcd.fillCircle(90, 80, 10, WHITE);
  M5.Lcd.fillCircle(230, 80, 10, WHITE);
  
}

void loop() {
  for (int i = 0; i < 180; i += 30) {
    M5.Lcd.setRotation(i);
    delay(50);
  }
}
