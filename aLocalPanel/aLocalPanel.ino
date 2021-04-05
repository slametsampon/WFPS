
#include <LiquidCrystal.h>//for LCD
#include <RTClib.h>

#include    "src\sequenceTimer\sequenceTimer.h"
#include    "src\serDevCmd\serDevCmd.h"

#include    "locPan.h"
#include    "fpSys.h"
#include    "commSer.h"

//Variables declaration

SequenceTimer SequenceMain("Sequence");

//Variables declaration for FPSys
DigitalInput        pbAuto(PIN_PB_AUTO);//use pin PIN_PB_AUTO for P/B
DigitalInput        pbManual(PIN_PB_MANUAL);//use pin PIN_PB_MANUAL for P/B
DigitalInput        pbReset(PIN_PB_RESET);//use pin PIN_PB_RESET for P/B
DigitalInput        pbTest(PIN_PB_TEST);

DigitalOutput       solenoidValve(PIN_SOLENOID_VALVE);
DigitalOutput       ledAuto(PIN_LED_AUTO);
DigitalOutput       ledManual(PIN_LED_MANUAL);
DigitalOutput       ledReset(PIN_LED_RESET);

AnalogInput         fireSensor(PIN_SENSOR);

PbAMRT              pbAMRT(&pbAuto, &pbManual, &pbReset, &pbTest);
LedAMR              ledAMR(&ledAuto, &ledManual, &ledReset);

FPSys               fpSys("fpSys - Fire Protection System");

//Variables declaration for LocPan
DigitalInput        addr0(PIN_ADDR0);//use pin PIN_ADDR0 for addressing
DigitalInput        addr1(PIN_ADDR1);//use pin PIN_ADDR1 for addressing
DigitalInput        addr2(PIN_ADDR2);//use pin PIN_ADDR2 for addressing

AnalogInput         keyAnalogIn(PIN_KEYPAD);

DigitalOutput       lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1

LiquidCrystal       lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad              keyPad(&keyAnalogIn);//declare keypad
serialCmd           serInput("Serial Command");
DipAddr             locAddr(&addr0, &addr1, &addr2);
ViewLcd             view(lcd);//declare view, part of MVC pattern
AccessDataMenu      accessMenu("Data Menu");//part of MVC pattern
AccessParam         accessParameter("Parameter");//part of MVC pattern
LocPan              locPan("LocPan-Local Panel");//local panel

//Variables declaration for commSer
CommSer             commSer("commSer - Serial Comm");

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char       LocPan::cmdInNbr=0;
unsigned char       AccessDataMenu::menuNbr=0;

//function declaration
void initPbLed();
void setupParameter();
void setupMenu();
void exceptionAct(int);

void setup() {

    Serial.begin(9600);
    Serial1.begin(9600);
    
    delay(500);

    keyAnalogIn.init(PULLUP);

    initPbLed();

    lifeLed.info();
    keyPad.info();

    //attachment all peripherals for locPan
    locPan.attachDipAddr(&locAddr);
    locPan.attachCmdIn(&keyPad);
    locPan.attachCmdIn(&serInput);
    locPan.attachView(&view);
    locPan.attachModelMenu(&accessMenu);
    locPan.attachModelParameter(&accessParameter);
    locPan.info();
    //After locPan attachDipAddr
    setupMenu();
    setupParameter();

    //attachment all peripherals for fpSys
    fpSys.attachModelParameter(&accessParameter);
    fpSys.attachFireSensor(&fireSensor);
    fpSys.attachPbAMRT(&pbAMRT);
    fpSys.attachLedAMR(&ledAMR);
    fpSys.attachSolenoidValve(&solenoidValve);
    fpSys.info();

    //attachment all peripherals for commSer
    commSer.attachModelParameter(&accessParameter);
}

// the loop function runs over and over again forever
void loop() {

  int exp = NO_EXCEPTION;

  lifeLed.blink(BLINK_NORMAL);//in milli second

  SequenceMain.execute();
  if(SequenceMain.isASecondEvent()){
    //commSer.execute();
  }

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
    case OPERATION_EXCEPTION:
      commSer.sendValue();
      break;
    
    case PARAMETER_EXCEPTION:
      fpSys.updateParameter();
      locPan.updateParameter();
      commSer.sendParameter();
      break;

    case REMOTE_OPERATION_EXCEPTION:
      /* code */
      break;
    
    case REMOTE_PARAMETER_EXCEPTION:
      /* code */
      break;

    default:
      break;
  }
}

void initPbLed(){
    Serial.println("LocalPanel : initPbLed()");

    //initialization switch
    pbAuto.init(REVERSE_TYPE);
    pbManual.init(REVERSE_TYPE);
    pbReset.init(REVERSE_TYPE);
    pbTest.init(REVERSE_TYPE);

    addr0.init(REVERSE_TYPE);
    addr1.init(REVERSE_TYPE);
    addr2.init(REVERSE_TYPE);

    solenoidValve.init(FORWARD_TYPE);

    //initialization LEDs
    lifeLed.init(FORWARD_TYPE);
    ledAuto.init(FORWARD_TYPE);
    ledManual.init(FORWARD_TYPE);
    ledReset.init(FORWARD_TYPE);
}

void setupMenu(){
  String locId = "Fire Zone-";
  dataMenu  dtMenu;

  Serial.println("LocalPanel-setupMenu()");

  dtMenu.isHasParam = false;
  dtMenu.Messages_0 ="Fire Protection System";
  dtMenu.Messages_1 ="Salman Alfarisi";
  accessMenu.add(dtMenu);

  //specific zone configuration  
  dtMenu.isHasParam = true;
  dtMenu.Messages_0 ="Fire Zone-1";
  dtMenu.Messages_1 ="Parameters";

  locId = String(locId + locPan.getAddress());
  locId.toCharArray(dtMenu.Messages_0,16);
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
  dtParam.alfaEma = ALFA_EMA;
  dtParam.alarm = NO_ALARM;
  dtParam.increment = 1.1;

  String locId = "ZONE-";
  locId = String(locId + locPan.getAddress());

  accessParameter.init(locId, dtParam);

}
