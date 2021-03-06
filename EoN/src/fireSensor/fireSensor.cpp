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

void FireSensor::info(){
  String str;
  str = String("Device : " + _sensorParam->id);
  Serial.println(str);

  str = String("Pin : " + _pin);
  Serial.println(str);

  str = String("Unit : " + _sensorParam->unit);
  Serial.println(str);

  str = String("High Range : " + String(_sensorParam->highRange));
  Serial.println(str);

  str = String("Low Range : " + String(_sensorParam->lowRange));
  Serial.println(str);

  str = String("High Limit : "+ String(_sensorParam->highLimit));
  Serial.println(str);

  str = String("Low Lmt : " + String(_sensorParam->lowLimit));
  Serial.println(str);

  str = String("AlfaEma : " + String(_sensorParam->alfaEma));
  Serial.println(str);

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
