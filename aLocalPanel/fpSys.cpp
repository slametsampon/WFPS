/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/
#include "fpSys.h"

FPSys::FPSys(String id):_id(id){}

void FPSys::init(){
    _pbAMRT->init();
    _ledAMR->init();
    _fireSensor->init(PULLUP,"_fireSensor");
    _solenoidValve->init(FORWARD_TYPE,"_solenoidValve");
    _buzzer->init(FORWARD_TYPE,"_buzzer");
}

void FPSys::info(){
    Serial.println("FPSys::info()=>Fire Protection System");
    
    _pbAMRT->info();
    _ledAMR->info();
    _fireSensor->info();
    _solenoidValve->info();
    _buzzer->info();

    Serial.println("<----->");
}

void FPSys::attachLedAMR(LedAMR *ledAMR){
    Serial.println("FPSys::attachLedAMR(LedAMR *ledAMR)");
    _ledAMR = ledAMR;
}

void FPSys::attachPbAMRT(PbAMRT *pbAMRT){
    Serial.println("FPSys::attachPbAMRT(PbAMRT *pbAMRT)");
    _pbAMRT = pbAMRT;
}

void FPSys::attachFireSensor(AnalogInput *fireSensor){
    Serial.println("FPSys::attachFireSensor(AnalogInput *fireSensor)");
    _fireSensor = fireSensor;

    this->updateParameter();
}

void FPSys::attachSolenoidValve(DigitalOutput *solenoidValve){
    Serial.println("FPSys::attachSolenoidValve(DigitalOutput *solenoidValve)");
    _solenoidValve = solenoidValve;
}

void FPSys::attachBuzzer(DigitalOutput *buzzer){
    Serial.println("FPSys::attachBuzzer(DigitalOutput *buzzer)");
    _buzzer = buzzer;
}

void FPSys::attachModelParameter(AccessParam *accessParameter){
    Serial.println("FPSys::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }

void FPSys::updateParameter(){
    _fireSensor->setParam(_accessParameter->getParam());
}
 
int FPSys::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void FPSys::execute(){
   
    int sensorStatus = _fireSensor->getStatus();//get sensor status
    int operationMode = _pbAMRT->getCmd(DEBOUNCING_TIME);//debouncing in milli second

    this->_logicOperation(operationMode, sensorStatus);//operation logic

    if((operationMode == MODE_AUTO) && (sensorStatus != NO_ALARM)) operationMode = MODE_AUTO_ON;
    _ledAMR->status(operationMode);//LED action

    //! get exceptions and MUST EXECUTE THE END
    _exception = _fireSensor->getException();
    if (_exception != NO_EXCEPTION){
        _accessParameter->setParam(PARAMETER_VALUE,_fireSensor->getValue());
        _accessParameter->setParam(PARAMETER_ALARM,sensorStatus);
        return;
    }

    _exception = _pbAMRT->getException();
    if (_exception != NO_EXCEPTION){
        _accessParameter->setParam(PARAMETER_OPERATION_MODE, operationMode);
        return;
    }

}

void FPSys::_logicOperation(int oprMode, int sensorStatus){

    //logic of operation
    boolean sensorAlarm = false;

    if (sensorStatus == LOW_ALARM)sensorAlarm=true;
    else if (sensorStatus == HIGH_ALARM)sensorAlarm=true;

    //activate buzzer
    if(sensorAlarm)_buzzer->blink(1000);
    else _buzzer->off();

    switch (oprMode){
        case MODE_AUTO:
            if (sensorAlarm)_solenoidValve->on();
            else _solenoidValve->off();
            break;
        
        case MODE_MANUAL:
            _solenoidValve->off();
            break;
        
        case MODE_MANUAL_ON:
            _solenoidValve->on();
            break;
        
        case MODE_READY:
            _solenoidValve->off();
            break;
        
        case MODE_RESET:
            _solenoidValve->off();
            break;
        
        case MODE_TEST:
            _buzzer->on();
            break;
        
        default:
            _solenoidValve->off();
            break;
    }
}