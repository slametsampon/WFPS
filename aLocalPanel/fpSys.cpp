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
    int operationMode = _pbAMRT->getCmd(DEBOUNCING_TIME);//debouncing in milli second

    this->_logicOperation(operationMode, sensorStatus);//operation logic

    if((operationMode == MODE_AUTO) && (sensorStatus == true)) operationMode = MODE_AUTO_ON;
    _ledAMR->status(operationMode);//LED action

    //report by exception
    if (_prevMode != operationMode){
        _prevMode = operationMode;
        Serial.println(_pbAMRT->status());
    }
}

boolean FPSys::_getSensorStatus(){
    boolean sensorStatus = false;

    param paramData = _accessParameter->getParam();

    //get sensor value
    int sensorVal = _fireSensor->getValue(ALFA_EMA);//AlfaEma in percentage
    int raw = _fireSensor->getRaw();

    //convert to actual unit
    int valUnit = map(sensorVal, 0, ADC_MAX, (long) paramData.lowRange, (long) paramData.highRange);

    //compare with low/high limit
    if(valUnit <= paramData.lowLimit)sensorStatus = true;
    else if(valUnit >= paramData.highLimit)sensorStatus = true;

    //report by exception
    if (_prevSensorVal != sensorVal){

        _prevSensorVal = sensorVal;
        Serial.print("valUnit : ");
        Serial.println(valUnit);

        Serial.print("sensorVal : ");
        Serial.println(sensorVal);

        Serial.print("raw : ");
        Serial.println(raw);

        Serial.print("sensorStatus : ");
        Serial.println(sensorStatus);
    }

    return sensorStatus;
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