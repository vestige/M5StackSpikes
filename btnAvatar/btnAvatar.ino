#include <M5Stack.h>
#include <Avatar.h>

#define SPEAKER_PIN 25

using namespace m5avatar;
Avatar avatar;

void setup() {
  M5.begin();
  avatar.init();  
  avatar.setExpression(Expression::Happy);

}

void beep(int freq, int duration, uint8_t volume) {
  int t = 1000000l / freq / 2;
  unsigned long start = millis();
  while ((millis() - start) < duration) {
    dacWrite(SPEAKER_PIN, 0);
    delayMicroseconds(t);
    dacWrite(SPEAKER_PIN, volume);
    delayMicroseconds(t);    
  }
  dacWrite(SPEAKER_PIN, 0);
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    //beep(440, 1000, 2);
    M5.Speaker.tone(262, 200);
    avatar.setExpression(Expression::Sad);
  }
  if (M5.BtnB.wasPressed()) {
    M5.Speaker.tone(330, 200);
    avatar.setExpression(Expression::Happy);
  }
  if (M5.BtnB.pressedFor(1000)) {
    avatar.setExpression(Expression::Neutral);
  }
  if (M5.BtnC.wasPressed()) {
    M5.Speaker.tone(392, 200);
    avatar.setExpression(Expression::Angry);
  }
  if (M5.BtnC.pressedFor(1000)) {
    avatar.setExpression(Expression::Neutral);
  }

}
