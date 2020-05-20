#include "SG90.h"
#include <M5Stack.h>

void SG90::begin(
    int pin,
    int ch
) {
    m_ch = ch;
    ledcSetup(m_ch, 50, 10);
    ledcAttachPin(pin, m_ch);
    SG90::write(0);
}

void SG90::write(
    int angle
) {
    ledcWrite(m_ch, map(constrain(angle, -90, 90), -90, 90, m_duty_max, m_duty_min));
}