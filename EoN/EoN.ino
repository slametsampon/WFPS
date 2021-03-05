#include "src\sequenceTimer\sequenceTimer.h"
#include "src\ledExt\ledExt.h"
#include "src\fireSensor\fireSensor.h"
#include "src\digitalOutput\DigitalOutput.h"

#include "pbAMR.h"
#include "ledAMR.h"
#include "FPSys.h"

#define PIN_SENSOR  A0

const int PIN_PB_AUTO = 4;
const int PIN_PB_MANUAL = 5;
const int PIN_PB_RESET = 6;

const int PIN_LED_AUTO = 2;
const int PIN_LED_MANUAL = 2;
const int PIN_LED_RESET = 3;

const int PIN_SOLENOID_VALVE = 7;

SequenceTimer SequenceMain("Sequence");

SwitchExt pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
SwitchExt pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
SwitchExt pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B

//LedExt ledAuto(PIN_LED_AUTO);
//LedExt ledManual(PIN_LED_MANUAL);
//LedExt ledReset(PIN_LED_RESET);
LedExt lifeLed(LED_BUILTIN);
DigitalOutput   solenoidValve(PIN_SOLENOID_VALVE);

PbAMR pbAmr(&pbAuto, &pbManual, &pbReset);
//LedAMR ledAmr(&ledAuto, &ledManual, &ledReset);

FireSensor  fireSensor(PIN_SENSOR);
FPSys   fpSys("Fire System");

void setup() {

    Serial.begin(115200);

    initPbLed();
    initSensor();

    //fpSys.attachLedAMR(&ledAmr);
    //fpSys.attachPbAMR(&pbAmr);
    fpSys.attachFireSensor(&fireSensor);
    fpSys.attachSolenoidValve(&solenoidValve);

    fpSys.info();

}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    SequenceMain.execute();
    if(SequenceMain.isASecondEvent()){
        //put process every second
    }

    fpSys.execute();
    
}

void initPbLed(){
    Serial.println("EoN : initPbLed()");
    //initialization LED's
    Serial.println("EoN : initPbLed()-lifeLed");
    lifeLed.init();
    //initialization switch
    //Serial.println("EoN : initPbLed()-pbAuto");
    //pbAuto.init();
    //Serial.println("EoN : initPbLed()-pbManual");
    //pbManual.init();
    //Serial.println("EoN : initPbLed()-pbReset");
    //pbReset.init();

    /*
    Serial.println("EoN : initPbLed()-ledAuto");
    ledAuto.init();
    Serial.println("EoN : initPbLed()-ledManual");
    ledManual.init();
    Serial.println("EoN : initPbLed()-ledReset");
    ledReset.init();
    */
}

void initSensor(){
    sensorParam param;
    Serial.println("EoN : initSensor()");

    //fire Zone1.
    param.id = "Smoke-1";
    param.unit = "%";
    param.highRange = 100;
    param.lowRange = 0;
    param.highLimit = 80;
    param.lowLimit = 40;

    fireSensor.setParameter(&param);
}