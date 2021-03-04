/*
    It is just for testing only
*/

#include "DigitalOutput.h"

DigitalOutput doTest(LED_BUILTIN);

void setup() {
    Serial.begin(115200);
    doTest.init(REVERSE_DO);
    Serial.println(doTest.info());
}

// the loop function runs over and over again forever
void loop() {
    //doTest.blink(500);//in milli second
}
