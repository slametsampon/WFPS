#include "src\ledExt\ledExt.h"
#include "src\sequenceTimer\sequenceTimer.h"
#include "pbAMR.h"
#include "ledAMR.h"

const char PIN_PB_AUTO = 2;
const char PIN_PB_MANUAL = 3;
const char PIN_PB_RESET = 4;

const char PIN_LED_AUTO = 5;
const char PIN_LED_MANUAL = 6;
const char PIN_LED_RESET = 7;

SwitchExt pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
SwitchExt pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
SwitchExt pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B

LedExt ledAuto(PIN_LED_AUTO);
LedExt ledManual(PIN_LED_MANUAL);
LedExt ledReset(PIN_LED_RESET);
LedExt lifeLed(LED_BUILTIN);

PbAMR pbAmr(&pbAuto, &pbManual, &pbReset);
LedAMR ledAmr(&ledAuto, &ledManual, &ledReset);

SequenceTimer SequenceMain("Sequence");

void setup() {

    Serial.begin(115200);

    initPbLed();
    oneShootLed();
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    SequenceMain.execute();
    if(SequenceMain.isASecondEvent()){
        //put process every second
    }
    
    ledAmr.info(pbAmr.getCmd(500));//debounce time in milli second
    pbAmr.info();
}

void initPbLed(){
    Serial.println("EoN : initPbLed()");
    //initialization switch
    pbAuto.init();
    pbManual.init();
    pbReset.init();

    //initialization LED's
    lifeLed.init();
    ledAuto.init();
    ledManual.init();
    ledReset.init();
}

void oneShootLed(){
    Serial.println("EoN : oneShootLed()");
    //one shoot
    ledAuto.on();
    ledManual.on();
    ledReset.on();

    delay(1000);

    ledAuto.off();
    ledManual.off();
    ledReset.off();
}