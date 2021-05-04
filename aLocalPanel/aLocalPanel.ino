
#include <LiquidCrystal.h>//for LCD
#include <RTClib.h>

#include    "src\serDevCmd\serDevCmd.h"
#include    "locPan.h"
#include    "fpSys.h"
#include    "commSer.h"

//Variables declaration for FPSys
DigitalInput        pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
DigitalInput        pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
DigitalInput        pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B
DigitalInput        pbTest(PIN_PB_TEST);

DigitalOutput       solenoidValve(PIN_SOLENOID_VALVE);
DigitalOutput       buzzer(PIN_BUZZER);
DigitalOutput       ledAuto(PIN_LED_AUTO);
DigitalOutput       ledManual(PIN_LED_MANUAL);
DigitalOutput       ledReset(PIN_LED_RESET);

AnalogInput         fireSensor(PIN_SENSOR);

PbAMRT              pbAMRT(&pbAuto, &pbManual, &pbReset, &pbTest);
LedAMR              ledAMR(&ledAuto, &ledManual, &ledReset);

FPSys               fpSys("fpSys");

//Variables declaration for LocPan
DigitalInput        addr0(PIN_ADDR0);//use pin PIN_ADDR0 for addressing
DigitalInput        addr1(PIN_ADDR1);//use pin PIN_ADDR1 for addressing
DigitalInput        addr2(PIN_ADDR2);//use pin PIN_ADDR2 for addressing

AnalogInput         keyAnalogIn(PIN_KEYPAD);

DigitalOutput       lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1

LiquidCrystal       lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad              keyPad(&keyAnalogIn);//declare keypad
serialCmd           serInput("serInput");
DipAddr             locAddr(&addr0, &addr1, &addr2);
ViewLcd             view(lcd);//declare view, part of MVC pattern
AccessDataMenu      accessMenu("accessMenu");//part of MVC pattern
AccessParam         accessParameter("accessParameter");//part of MVC pattern
LocPan              locPan("locPan");//local panel

//Variables declaration for commSer
CommSer             commSer("commSer");

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char       LocPan::cmdInNbr=0;
unsigned char       AccessDataMenu::menuNbr=0;

//function declaration
void exceptionAct(int);

void setup() {

    Serial.begin(9600);
    Serial1.begin(9600);
    
    delay(500);

    lifeLed.init(FORWARD_TYPE,"lifeLed");
    lifeLed.info();

    //attachment all peripherals for locPan
    locPan.attachDipAddr(&locAddr);
    locPan.attachCmdIn(&keyPad);
    locPan.attachCmdIn(&serInput);
    locPan.attachView(&view);
    locPan.attachModelMenu(&accessMenu);
    locPan.attachModelParameter(&accessParameter);
    //init for peripherals
    locPan.init();

    locPan.info();
    //attachment all peripherals for fpSys
    fpSys.attachModelParameter(&accessParameter);
    fpSys.attachFireSensor(&fireSensor);
    fpSys.attachPbAMRT(&pbAMRT);
    fpSys.attachLedAMR(&ledAMR);
    fpSys.attachSolenoidValve(&solenoidValve);
    fpSys.attachBuzzer(&buzzer);
    //init for peripherals
    fpSys.init();

    fpSys.info();

    //attachment all peripherals for commSer
    commSer.attachModelParameter(&accessParameter);
}

// the loop function runs over and over again forever
void loop() {

  int exp = NO_EXCEPTION;

  lifeLed.blink(BLINK_NORMAL);//in milli second

  locPan.menu();
  fpSys.execute();
  commSer.execute();

  //get exception, and action as per exception code
  exceptionAct(locPan.getException());//get parameter exception
  exceptionAct(fpSys.getException());//get operation exception
  exceptionAct(commSer.getException());//get remote exception

}

void exceptionAct(int exp){
  switch (exp)  {
    case LOCAL_OPERATION_EXCEPTION:
      commSer.sendValue();
      break;
    
    case LOCAL_PARAMETER_EXCEPTION:
      fpSys.updateParameter();
      locPan.updateParameter();
      commSer.sendParameter();
      break;

    case REMOTE_OPERATION_EXCEPTION:
      fpSys.execute();//1. check status fpSys (getValue, getMode)
      break;
    
    case REMOTE_PARAMETER_EXCEPTION:
      fpSys.updateParameter();
      locPan.updateParameter();
      fpSys.execute();//1. check status fpSys (getValue, getMode)
      break;

    default:
      break;
  }
}

