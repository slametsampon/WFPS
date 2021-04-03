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

void FPSys::attachModelParameter(AccessParam *accessParameter){
    Serial.println("FPSys::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
 
void FPSys::execute(){

    
    boolean sensorStatus = this->_getSensorStatus();//get sensor status
    int operationMode = _pbAMRT->getCmd(500);//debouncing in milli second

    _ledAMR->status(operationMode);//LED action
    this->_logicOperation(operationMode, sensorStatus);//operation logic

    //report by exception
    if (_prevMode != operationMode){
        _prevMode = operationMode;
        Serial.println(_pbAMRT->status());
    }
}

boolean FPSys::_getSensorStatus(){
    boolean status;

    param paramData = _accessParameter->getParam();

    //get sensor value
    int sensorVal = _fireSensor->getValue(80);//AlfaEma in percentage
    int raw = _fireSensor->getRaw();

    //convert to actual unit

    //compare with low/high limit

    //report by exception
    if (_prevSensorVal != sensorVal){

        _prevSensorVal = sensorVal;
        Serial.print("sensorVal : ");
        Serial.println(sensorVal);

        Serial.print("raw : ");
        Serial.println(raw);
    }

    return status;
}

void FPSys::_logicOperation(int oprMode, boolean sensorStatus){

    //logic of operation
    switch (oprMode){
        case MODE_AUTO:
            if (sensorStatus)_solenoidValve->on();
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