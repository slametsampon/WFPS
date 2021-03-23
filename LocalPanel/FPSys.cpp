/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/
#include "FPSys.h"

FPSys::FPSys(String id):_id(id){}

void FPSys::info(){
    Serial.println("FPSys::info()=>Fire Protection System");
    _dipAddr->info();
    _pbAMR->info();
    _ledAMR->info();
    Serial.println(_solenoidValve->info());
    Serial.println(_fireSensor->info());
}

void FPSys::attachLedAMR(LedAMR *ledAMR){
    Serial.println("FPSys::attachLedAMR(LedAMR *ledAMR)");
    _ledAMR = ledAMR;
}

void FPSys::attachPbAMR(PbAMR *pbAMR){
    Serial.println("FPSys::attachPbAMR(PbAMR *pbAMR)");
    _pbAMR = pbAMR;
}

void FPSys::attachDipAddr(DipAddr *dipAddr){
    Serial.println("FPSys::attachDipAddr(DipAddr *dipAddr)");
    _dipAddr = dipAddr;
}

void FPSys::attachFireSensor(DigitalInput *fireSensor){
    Serial.println("FPSys::attachFireSensor(SwitchExt *fireSensor)");
    _fireSensor = fireSensor;
}

void FPSys::attachSolenoidValve(DigitalOutput *solenoidValve){
    Serial.println("FPSys::attachSolenoidValve(DigitalOutput *solenoidValve)");
    _solenoidValve = solenoidValve;
}

void FPSys::execute(){

    //measure and putting in sensorParam
    boolean sensorStatus = _fireSensor->isStatus(500);//debouncing in milli second

    //get input command from push button
    _operationMode = _pbAMR->getCmd(500);//debouncing in milli second
    _ledAMR->status(_operationMode);

    //logic of operation
    switch (_operationMode){
        case PB_AUTO:
            if (sensorStatus)_solenoidValve->on();
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
