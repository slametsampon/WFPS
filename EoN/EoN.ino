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

#include <LiquidCrystal.h>//for LCD
#include <RTClib.h>

#include "src\sequenceTimer\sequenceTimer.h"
#include "src\ledExt\ledExt.h"
#include "src\switchExt\switchExt.h"
#include "src\digitalOutput\DigitalOutput.h"

#include    "pbAMR.h"
#include    "ledAMR.h"
#include    "FPSys.h"
#include    "dipAddr.h"
#include    "localPanel.h"

#define PIN_KEYPAD A0 // pin Analog Keypad

const int LCD_RS = 8;
const int LCD_EN = 9;
const int LCD_D4 = 4;
const int LCD_D5 = 5;
const int LCD_D6 = 6;
const int LCD_D7 = 7;

const int PIN_PB_AUTO       = 23; //D23
const int PIN_PB_MANUAL     = 25; //D25
const int PIN_PB_RESET      = 27; //D27

const int PIN_ADDR0         = 29; //D29
const int PIN_ADDR1         = 31; //D31
const int PIN_ADDR2         = 33; //D33
const int PIN_SENSOR        = 35; //D35

const int PIN_LED_AUTO      = 22; //D22
const int PIN_LED_MANUAL    = 24; //D23
const int PIN_LED_RESET     = 26; //D26

const int PIN_SOLENOID_VALVE = 28; //D0

SequenceTimer SequenceMain("Sequence");

SwitchExt       addr0(PIN_ADDR0);//use pin PIN_ADDR0 for addressing
SwitchExt       addr1(PIN_ADDR1);//use pin PIN_ADDR1 for addressing
SwitchExt       addr2(PIN_ADDR2);//use pin PIN_ADDR2 for addressing

SwitchExt       pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
SwitchExt       pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
SwitchExt       pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B
DigitalOutput   solenoidValve(PIN_SOLENOID_VALVE);

LedExt          ledAuto(PIN_LED_AUTO);
LedExt          ledManual(PIN_LED_MANUAL);
LedExt          ledReset(PIN_LED_RESET);
LedExt          lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1

SwitchExt       fireSensor(PIN_SENSOR);

DipAddr         eonAddr(&addr0, &addr1, &addr2);
PbAMR           pbAMR(&pbAuto, &pbManual, &pbReset);
LedAMR          ledAMR(&ledAuto, &ledManual, &ledReset);

FPSys           fpSys("Fire System");

//Variables declaration
LiquidCrystal   lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad          keyPad(PIN_KEYPAD);//declare keypad
serialCmd       serInput("Serial Command");
ViewLcd         view(lcd);//declare view, part of MVC pattern
LocalPanel      localPanel("localPanel");

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char LocalPanel::cmdInNbr=0;

void setup() {

    Serial.begin(115200);
    delay(500);

    initPbLed();

    //attachment all peripherals
    fpSys.attachDipAddr(&eonAddr);
    fpSys.attachLedAMR(&ledAMR);
    fpSys.attachPbAMR(&pbAMR);
    fpSys.attachFireSensor(&fireSensor);
    fpSys.attachSolenoidValve(&solenoidValve);

    //attachment all peripherals
    localPanel.attachCmdIn(&keyPad);
    localPanel.attachView(&view);

    String str;
    str = String("lifeLed \n");//with new line
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
    pbAuto.init("pbAuto");
    pbManual.init("pbManual");
    pbReset.init("pbReset");
    solenoidValve.init(FORWARD_DO);

    addr0.init("addr0");
    addr1.init("addr1");
    addr2.init("addr2");

    fireSensor.init("fireSensor");

    //initialization LEDs
    lifeLed.init("lifeLed");
    ledAuto.init("ledAuto");
    ledManual.init("ledManual");
    ledReset.init("ledReset");
}
