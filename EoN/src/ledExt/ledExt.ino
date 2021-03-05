/*
    It is just for testing only
*/

#include "ledExt.h"
LedExt blinkTest(LED_BUILTIN);

void setup() {
    Serial.begin(115200);
    delay(500);
    blinkTest.init();
    Serial.println(blinkTest.info());
}

// the loop function runs over and over again forever
void loop() {
    blinkTest.blink(500);//in milli second
}
