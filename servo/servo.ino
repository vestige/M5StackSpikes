#include <M5Stack.h>
#include "SG90.h"

SG90 sg90;

void setup(    
) {
    M5.begin();

    sg90.begin(2, 15);

    for(int angle = -90; angle <= 90; angle += 5) {
        sg90.write(angle);
        delay(100);
    }
}

void loop() {

}