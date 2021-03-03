/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/
#include "FPSys.h"

FPSys::FPSys(String id):_id(id){}

void FPSys::info(){
    Serial.println("FPSys::info()=>Fire Protection System");
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
