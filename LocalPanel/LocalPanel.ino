
#include <LiquidCrystal.h>//for LCD
#include <RTClib.h>

#include    "src\analogInput\param.h"
#include    "src\sequenceTimer\sequenceTimer.h"
#include    "src\digitalInput\digitalInput.h"
#include    "src\digitalOutput\DigitalOutput.h"

#include    "model.h"
#include    "pbAMR.h"
#include    "KeyPad.h"
#include    "ledAMR.h"
#include    "dipAddr.h"

#include    "FPSys.h"
#include    "locPan.h"
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
DigitalInput        fireSensor(PIN_SENSOR);
PbAMR               pbAMR(&pbAuto, &pbManual, &pbReset);
LedAMR              ledAMR(&ledAuto, &ledManual, &ledReset);
FPSys               fpSys("fpSys-Fire System");

//Variables declaration for LocPan
LiquidCrystal       lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad              keyPad(PIN_KEYPAD);//declare keypad
serialCmd           serInput("Serial Command");
DipAddr             eonAddr(&addr0, &addr1, &addr2);
ViewLcd             view(lcd);//declare view, part of MVC pattern
AccessDataMenu      accessMenu("Data Menu");//part of MVC pattern
AccessParam         accessParameter("Parameter");//part of MVC pattern
LocPan              locPan("LocPan-Local Panel");//local panel

//Variables declaration for CommSer
CommSer             commSer("commSer-Communication Serial");//Serail communication to/from EoN

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char       LocPan::cmdInNbr=0;
unsigned char       AccessDataMenu::menuNbr=0;

//function declaration
void initPbLed();
void setupParameter();
void setupMenu();

void setup() {

    Serial.begin(9600);
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
    fpSys.info();

    //attachment all peripherals for locPan
    locPan.info();
    locPan.attachCmdIn(&keyPad);
    locPan.attachCmdIn(&serInput);
    locPan.attachView(&view);
    locPan.attachModelMenu(&accessMenu);
    locPan.attachModelParameter(&accessParameter);

    //attachment all peripherals for locPan
    commSer.info();
    commSer.attachModelParameter(&accessParameter);

    String str;
    str = String("lifeLed \n");//with new line
    str = String(str + lifeLed.info());
    Serial.println(str);
    
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    SequenceMain.execute();
    if(SequenceMain.isASecondEvent()){
        //put process every second
    }

    //fpSys.execute();
    //locPan.menu();
    //commSer.execute();
}

void initPbLed(){
    Serial.println("LocalPanel : initPbLed()");

    //initialization switch
    pbAuto.init(REVERSE_DI);
    pbManual.init(REVERSE_DI);
    pbReset.init(REVERSE_DI);
    solenoidValve.init(FORWARD_DO);

    addr0.init(REVERSE_DI);
    addr1.init(REVERSE_DI);
    addr2.init(REVERSE_DI);

    fireSensor.init("fireSensor");

    //initialization LEDs
    lifeLed.init(FORWARD_DO);
    ledAuto.init(FORWARD_DO);
    ledManual.init(FORWARD_DO);
    ledReset.init(FORWARD_DO);
}

void setupMenu(){
  dataMenu  dtMenu;

  Serial.println("LocalPanel-setupMenu()");

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
  Serial.println("LocalPanel-setupParameter()");

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
