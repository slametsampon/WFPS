/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/
#include "FPSys.h"

FPSys::FPSys(String id):_id(id){}

void FPSys::info(){
    Serial.println("FPSys::info()=>Fire Protection System");
    _pbAMR->info();
    _ledAMR->info();
    Serial.println(_solenoidValve->info());
    _fireSensor->info();
}

void FPSys::attachLedAMR(LedAMR *ledAMR){
    Serial.println("FPSys::attachLedAMR(LedAMR *ledAMR)");
    _ledAMR = ledAMR;
}

void FPSys::attachPbAMR(PbAMR *pbAMR){
    Serial.println("FPSys::attachPbAMR(PbAMR *pbAMR)");
    _pbAMR = pbAMR;
}

void FPSys::attachFireSensor(FireSensor *fireSensor){
    Serial.println("FPSys::attachFireSensor(FireSensor *fireSensor)");
    _fireSensor = fireSensor;
}

void FPSys::attachSolenoidValve(DigitalOutput *solenoidValve){
    Serial.println("FPSys::attachSolenoidValve(DigitalOutput *solenoidValve)");
    _solenoidValve = solenoidValve;
}

void FPSys::execute(){

    //measure and putting in sensorParam
    _fireSensor->getValue();
    int sensorStatus = _fireSensor->getStatus();

    //get input command from push button
    _operationMode = _pbAMR->getCmd(500);//debouncing in milli second
    _ledAMR->status(_operationMode);

    //logic of operation
    switch (_operationMode){
        case PB_AUTO:
            //if (_fireSensor->getStatus()==LOW_ALARM)_solenoidValve->on();//if we use HIGH_ALARM
            if (sensorStatus == HIGH_ALARM)_solenoidValve->on();//if we use HIGH_ALARM
            else _solenoidValve->off();
            break;
        
        case PB_MANUAL:
            _solenoidValve->off();
            break;
        
        case PB_MANUAL_ON:
            _solenoidValve->on();
            break;
        
        case PB_READY:
            _solenoidValve->off();
            break;
        
        case PB_RESET:
            _solenoidValve->off();
            break;
        
        default:
            _solenoidValve->off();
            break;
    }
}
