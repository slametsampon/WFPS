/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/
#include "fpSys.h"

FPSys::FPSys(String id):_id(id){
    _prevMode = DEFAULT_INDEX;
}

void FPSys::info(){
    Serial.println("FPSys::info()=>Fire Protection System");
    
    _pbAMRT->info();
    _ledAMR->info();
    _fireSensor->info();
    _solenoidValve->info();

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
}

void FPSys::attachSolenoidValve(DigitalOutput *solenoidValve){
    Serial.println("FPSys::attachSolenoidValve(DigitalOutput *solenoidValve)");
    _solenoidValve = solenoidValve;
}

void FPSys::execute(){
   
    int sensorStatus = _fireSensor->getStatus();//get sensor status
    int operationMode = _pbAMRT->getCmd(DEBOUNCING_TIME);//debouncing in milli second

    this->_logicOperation(operationMode, sensorStatus);//operation logic

    if((operationMode == MODE_AUTO) && (sensorStatus != NO_ALARM)) operationMode = MODE_AUTO_ON;
    _ledAMR->status(operationMode);//LED action

}

void FPSys::_logicOperation(int oprMode, int sensorStatus){

    //logic of operation
    boolean sensorAlarm = false;

    if (sensorStatus == LOW_ALARM)sensorAlarm=true;
    else if (sensorStatus == HIGH_ALARM)sensorAlarm=true;

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
        
        default:
            _solenoidValve->off();
            break;
    }
}