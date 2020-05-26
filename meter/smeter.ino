#include <M5Stack.h>

#define NBIN 30
static int16_t s_ring[NBIN];
static int s_curr;
static int16_t s_bg;
static int s_delay = 20000;
static unsigned long s_tm;

void setup() {
  M5.begin();
  M5.Power.begin();

  Serial2.begin(9600);
  delay(100);

  s_tm = millis();
  
  s_bg = M5.Lcd.color565(253, 253, 253);

  M5.Lcd.fillScreen(BLACK);
  drawArcScale();
}

void addValue(int16_t value) {
  s_curr += 1;
  if (s_curr >= NBIN) s_curr = 0;
  s_ring[s_curr] = value;
  drawArcValue();
}

void fillQ(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, int16_t color) {
  M5.Lcd.fillTriangle(x0, y0, x1, y1, x2, y2, color);
  M5.Lcd.fillTriangle(x2, y2, x3, y3, x0, y0, color);
}

void drawArc(int16_t x, int16_t y, int16_t inner, int16_t outer, int16_t angle, int16_t angle2, int16_t color) {
  float si = sin(radians(angle));
  float co = cos(radians(angle));
  float x0 = x + inner * si;
  float y0 = y + inner * co;
  float x1 = x + outer * si;
  float y1 = y + outer * co;

  float si2 = sin(radians(angle2));
  float co2 = cos(radians(angle2));
  float x3 = x + inner * si2;
  float y3 = y + inner * co2;
  float x2 = x + outer * si2;
  float y2 = y + outer * co2;

  fillQ(x0, y0, x1, y1, x2, y2, x3, y3, color);
}

void drawArcScale() {
  M5.Lcd.fillEllipse(160, 120, 120, 120, s_bg);
}

void drawArcOne(int index, int inner, int outer, int16_t color) {
  drawArc(160, 120, inner, outer, -index * 12 + 0, -index * 12 + 5, color);
  drawArc(160, 120, inner, outer, -index * 12 + 5, -index * 12 + 10, color);
}

void eraseArcOne(int index, int16_t color) {
  drawArc(160, 120, 66, 119, -index * 12 -1, -index * 12 + 5, color);
  drawArc(160, 120, 66, 119, -index * 12 + 5, -index * 12 + 12, color);
}

int16_t barMap(int16_t value) {
  if (value <= 400) {
    return 68;
  } else if (value <= 2000) {
    return (value - 400) / 1600.0 * 50 + 68;
  } else if (value <= 3600) {
    return (value - 2000) / 1600.0 * 50 + 68;
  } else {
    return 118;
  }
}

void drawArcValue() {
  int16_t value = s_ring[s_curr];
  int16_t bar = barMap(value);
  
  M5.Lcd.setCursor(140, 120);
  M5.Lcd.setTextColor(DARKGREY, s_bg);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("ppm");
  M5.Lcd.setCursor(115, 90);

  if (value <= 1000) {
    M5.Lcd.setTextColor(BLUE, s_bg);
    drawArcOne(s_curr, bar, 118, CYAN);
  } else if (value <= 2000)  {
    M5.Lcd.setTextColor(GREEN, s_bg);
    drawArcOne(s_curr, bar, 118, GREEN);
  } else {
    M5.Lcd.setTextColor(RED, s_bg);
    drawArcOne(s_curr, 68, bar, RED);
  }
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("%4d", value);

  eraseArcOne(s_curr + 1, s_bg);
}

void getCO2() {
  static byte getcmd[9] = { 0xff, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };
  byte value[9];
  int val;
      
  Serial2.write(getcmd, 9);
  if (Serial2.available()) {
    Serial2.readBytes(value, 9);

    if (value[0] == 0xff && value[1] == 0x86) {
      val = value[2] * 256 + value[3];
      addValue(val);
      drawArcValue();
    }
  }
}

void loop() {
  static int s_progress = 0;
  static int s_delta = 100;

  s_progress += s_delta;
  if (s_progress > 3600) {
    s_delta = -100;
  } else if (s_progress < 400) {
    s_delta = 100;
  }

  addValue(s_progress);
  drawArcValue();
  
  delay(1000);
}

void printInterval() {
  M5.Lcd.setCursor(115, 90);
  M5.Lcd.setTextColor(BLUE, s_bg);
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("%3dS", s_delay / 1000);
}

void loop0() {
  M5.update();

  if (M5.BtnA.wasReleased()) {
    s_delay = 20000;
    printInterval();
  } else if (M5.BtnB.wasReleased()) {
    s_delay = 60000;
    printInterval();
  } else if (M5.BtnC.wasReleased()) {
    s_delay = 120000;
    printInterval();
  } else if (M5.BtnB.wasReleasefor(700)) {
    s_delay = 15000;
    printInterval();
  }

  if (millis() - s_tm > s_delay) {
    getCO2();
    s_tm = millis();
  }
  delay(1000);
}