/*
  fireSensor.h - Library untuk FireSensor
  Dibuat Oleh : Sam March 02, 2021
*/

#include    "fireSensor.h"

FireSensor::FireSensor(int pin):_pin(pin){}

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

String FireSensor::info(){
  String str;
  str = String("Device : " + _sensorParam->id);
  str = String(str + "\n");//new line

  str = String(str + "Pin : ");
  str = String(str + _pin);
  str = String(str + "\n");//new line

  str = String(str + "Unit : ");
  str = String(str + _sensorParam->unit);
  str = String(str + "\n");//new line

  str = String(str + "High Range : ");
  str = String(str + _sensorParam->highRange);
  str = String(str + "\n");//new line

  str = String(str + "Low Range : ");
  str = String(str + _sensorParam->lowRange);
  str = String(str + "\n");//new line

  str = String(str + "High Limit : ");
  str = String(str + _sensorParam->highLimit);
  str = String(str + "\n");//new line

  str = String(str + "Low Lmt : ");
  str = String(str + _sensorParam->lowLimit);
  str = String(str + "\n");//new line

  str = String(str + "AlfaEma : ");
  str = String(str + _sensorParam->alfaEma);

  return str;

}

int FireSensor::getStatus(){
    int sts = NORMAL;
    if (_sensorParam->lowAlarm){
        sts = LOW_ALARM;
    }
    if (_sensorParam->highAlarm){
        sts = HIGH_ALARM;
    }
    return sts;
}

//measure and putting in _sensorParam
void FireSensor::getValue(){
	unsigned long tempVal, pv;
		//calculate for EMA filter
		tempVal = (analogRead(_pin)*_sensorParam->alfaEma + (100-_sensorParam->alfaEma)*_PV_Raw)/100;

		_PV_Raw = tempVal;// after filtering
		pv = map(tempVal,0, 1023,_sensorParam->lowRange , _sensorParam->highRange);
    _sensorParam->value = pv;
}
