/*
  fireSensor.h - Library untuk FireSensor
  Dibuat Oleh : Sam March 02, 2021
*/

#include    "fireSensor.h"

FireSensor::FireSensor(char pin):_pin(pin){}

void FireSensor::setParameter(sensorParam *param){
    _sensorParam = param;
}

sensorParam *FireSensor::getParameter(){
    return _sensorParam;
}

String FireSensor::toString(){
  String str = _sensorParam->id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + _sensorParam->unit);
  if (_sensorParam->lowAlarm){
    alm = "(L)";
  }
  if (_sensorParam->highAlarm){
    alm = "(H)";
  }
  str =  String(str + alm);
  return str;
}

char FireSensor::getStatus(){
    char sts = NORMAL;
    if (_sensorParam->lowAlarm){
        sts = LOW_ALARM;
    }
    if (_sensorParam->highAlarm){
        sts = HIGH_ALARM;
    }
    return sts;
}

