/*
Pin Function ESP-8266 Pin
Wemos D1 Mini
TX TXD TXD
RX RXD RXD
A0 Analog in(max 3.3V) A0
D0 IO GPIO16
D1 IO, SCL GPIO5
D2 IO, SDA GPIO4
D3 IO,Pull-up GPIO0
D4 IO,pull-up,LED GPIO2
D5 IO, SCK GPIO14
D6 IO, MISO GPIO12
D7 IO, MOSI GPIO13
D8 IO,pull-down, SS GPIO15
*/

#include "src\sequenceTimer\sequenceTimer.h"
#include "src\ledExt\ledExt.h"
#include "src\switchExt\switchExt.h"
#include "src\fireSensor\fireSensor.h"
#include "src\digitalOutput\DigitalOutput.h"

#include    "pbAMR.h"
#include    "ledAMR.h"
#include    "FPSys.h"

#define PIN_SENSOR  A0

const int PIN_PB_AUTO     = 14; //D5
const int PIN_PB_MANUAL   = 12; //D6
const int PIN_PB_RESET    = 13; //D7

const int PIN_LED_AUTO    = 5; //D1
const int PIN_LED_MANUAL  = 4; //D2
const int PIN_LED_RESET   = 0; //D3

const int PIN_SOLENOID_VALVE = 16; //D0

SequenceTimer SequenceMain("Sequence");

SwitchExt pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
SwitchExt pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
SwitchExt pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B
DigitalOutput   solenoidValve(PIN_SOLENOID_VALVE);

LedExt ledAuto(PIN_LED_AUTO);
LedExt ledManual(PIN_LED_MANUAL);
LedExt ledReset(PIN_LED_RESET);
LedExt lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1

FireSensor  fireSensor(PIN_SENSOR);

PbAMR   pbAMR(&pbAuto, &pbManual, &pbReset);
LedAMR   ledAMR(&ledAuto, &ledManual, &ledReset);
FPSys   fpSys("Fire System");

void setup() {

    Serial.begin(115200);
    delay(500);

    initPbLed();
    initSensor();

    fpSys.attachLedAMR(&ledAMR);
    fpSys.attachPbAMR(&pbAMR);
    fpSys.attachFireSensor(&fireSensor);
    fpSys.attachSolenoidValve(&solenoidValve);

    String str;
    str = String("_ledAuto \n");//with new line
    str = String(str + lifeLed.info());
    Serial.println(str);
    
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

    //initialization switch
    pbAuto.init();
    pbManual.init();
    pbReset.init();
    solenoidValve.init(FORWARD_DO);

    //initialization LEDs
    lifeLed.init();
    ledAuto.init();
    ledManual.init();
    ledReset.init();
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
    param.alfaEma = 80;

    fireSensor.setParameter(&param);
}

