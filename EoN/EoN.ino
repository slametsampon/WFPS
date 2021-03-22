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

#include    "src\analogInput\param.h"
#include    "src\sequenceTimer\sequenceTimer.h"
#include    "src\digitalInput\digitalInput.h"
#include    "src\digitalOutput\DigitalOutput.h"

#include    "Model.h"
#include    "pbAMR.h"
#include    "KeyPad.h"
#include    "ledAMR.h"
#include    "dipAddr.h"

#include    "FPSys.h"
#include    "localPanel.h"
#include    "commSer.h"

#define PIN_KEYPAD A0 // pin Analog Keypad

const int LCD_RS            = 8;
const int LCD_EN            = 9;
const int LCD_D4            = 4;
const int LCD_D5            = 5;
const int LCD_D6            = 6;
const int LCD_D7            = 7;

const int PIN_PB_AUTO       = 23; 
const int PIN_PB_MANUAL     = 25; 
const int PIN_PB_RESET      = 27; 

const int PIN_ADDR0         = 29; 
const int PIN_ADDR1         = 31; 
const int PIN_ADDR2         = 33; 
const int PIN_SENSOR        = 35; 

const int PIN_LED_AUTO      = 22; 
const int PIN_LED_MANUAL    = 24; 
const int PIN_LED_RESET     = 26; 

const int PIN_SOLENOID_VALVE = 28; 

//Variables declaration

SequenceTimer SequenceMain("Sequence");

//Variables declaration for FPSys
DigitalInput        addr0(PIN_ADDR0);//use pin PIN_ADDR0 for addressing
DigitalInput        addr1(PIN_ADDR1);//use pin PIN_ADDR1 for addressing
DigitalInput        addr2(PIN_ADDR2);//use pin PIN_ADDR2 for addressing
DigitalInput        pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
DigitalInput        pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
DigitalInput        pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B
DigitalOutput       solenoidValve(PIN_SOLENOID_VALVE);
DigitalOutput       ledAuto(PIN_LED_AUTO);
DigitalOutput       ledManual(PIN_LED_MANUAL);
DigitalOutput       ledReset(PIN_LED_RESET);
DigitalOutput       lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1
DigitalInput       fireSensor(PIN_SENSOR);
PbAMR           pbAMR(&pbAuto, &pbManual, &pbReset);
LedAMR          ledAMR(&ledAuto, &ledManual, &ledReset);
FPSys           fpSys("EoN-Fire System");

//Variables declaration for LocalPanel
LiquidCrystal   lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad          keyPad(PIN_KEYPAD);//declare keypad
serialCmd       serInput("Serial Command");
DipAddr         eonAddr(&addr0, &addr1, &addr2);
ViewLcd         view(lcd);//declare view, part of MVC pattern
AccessDataMenu  accessMenu("Data Menu");//part of MVC pattern
AccessParam     accessParameter("Parameter");//part of MVC pattern
LocalPanel      localPanel("EoN-localPanel");

//Variables declaration for CommSer
CommSer         commSer("EoN-Serial");

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char LocalPanel::cmdInNbr=0;
unsigned char AccessDataMenu::menuNbr=0;

//function declaration
void initPbLed();
void setupParameter();
void setupMenu();

void setup() {

    Serial.begin(115200);
    delay(500);

    initPbLed();
    setupMenu();
    setupParameter();

    //attachment all peripherals for fpSys
    fpSys.attachDipAddr(&eonAddr);
    fpSys.attachLedAMR(&ledAMR);
    fpSys.attachPbAMR(&pbAMR);
    fpSys.attachFireSensor(&fireSensor);
    fpSys.attachSolenoidValve(&solenoidValve);

    //attachment all peripherals for localPanel
    localPanel.attachCmdIn(&keyPad);
    localPanel.attachCmdIn(&serInput);
    localPanel.attachView(&view);
    localPanel.attachModelMenu(&accessMenu);
    localPanel.attachModelParameter(&accessParameter);

    //attachment all peripherals for localPanel
    commSer.attachModelParameter(&accessParameter);

    String str;
    str = String("lifeLed \n");//with new line
    str = String(str + lifeLed.info());
    Serial.println(str);
    
    fpSys.info();
    localPanel.info();
    commSer.info();
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    SequenceMain.execute();
    if(SequenceMain.isASecondEvent()){
        //put process every second
    }

    fpSys.execute();
    localPanel.menu();
    commSer.execute();
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

void setupMenu(){
  dataMenu  dtMenu;

  Serial.println("EoN-setupMenu()");

  dtMenu.isHasParam = false;
  dtMenu.Messages_0 ="Fire Protection System";
  dtMenu.Messages_1 ="Salman Alfarisi";
  accessMenu.add(dtMenu);

  dtMenu.isHasParam = true;
  dtMenu.Messages_0 ="Fire Zone-1";
  dtMenu.Messages_1 ="Parameter 1";
  accessMenu.add(dtMenu);

}

void setupParameter(){
  param dtParam;
  Serial.println("EoN-setupParameter()");

  //fire Zone1.
  dtParam.unit = "%";
  dtParam.value = 51;
  dtParam.highRange = 100;
  dtParam.lowRange = 0;
  dtParam.highLimit = 80;
  dtParam.lowLimit = 40;
  dtParam.increment = 1.1;

  accessParameter.init("ZONE - 1", dtParam);

}