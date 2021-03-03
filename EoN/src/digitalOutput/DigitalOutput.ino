/*
    It is just for testing only
*/

#include "DigitalOutput.h"

DigitalOutput blinkTest(LED_BUILTIN);

void setup() {
    Serial.begin(115200);
    blinkTest.init(REVERSE_DO);
    Serial.println(blinkTest.info());
}

// the loop function runs over and over again forever
void loop() {
    blinkTest.blink(500);//in milli second
}
