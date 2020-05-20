#ifndef SG90_H
#define SG90_H

class SG90 {
public:
    SG90(void) {};
    virtual ~SG90(void) {};
    void begin(int pin, int ch);
    void write(int angle);
private:
    int m_ch;
    const int m_duty_min = 26; // 0.5 ms / 20 ms * 1024 (-90 angle) 
    const int m_duty_max = 123; // 2.4 ms / 20 ms * 1024 (+90 angle)
};
#endif // SG90_H