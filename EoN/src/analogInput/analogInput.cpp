/*
  fireSensor.h - Library untuk AnalogInput
  Dibuat Oleh : Sam March 02, 2021
*/

#include    "analogInput.h"

AnalogInput::AnalogInput(char pin):_pin(pin){}

void AnalogInput::setParameter(aiParam *param){
    _aiParam = param;
}

aiParam *AnalogInput::getParameter(){
    return _aiParam;
}

String AnalogInput::toString(){
  String str = _aiParam->id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + _aiParam->unit);
  if (_aiParam->lowAlarm){
    alm = "(L)";
  }
  if (_aiParam->highAlarm){
    alm = "(H)";
  }
  str =  String(str + alm);
  return str;
}

void AnalogInput::info(){
  String str;
  str = String("Device : " + _aiParam->id);
  Serial.println(str);

  str = String("Pin : " + _pin);
  Serial.println(str);

  str = String("Unit : " + _aiParam->unit);
  Serial.println(str);

  str = String("High Range : " + String(_aiParam->highRange));
  Serial.println(str);

  str = String("Low Range : " + String(_aiParam->lowRange));
  Serial.println(str);

  str = String("High Limit : "+ String(_aiParam->highLimit));
  Serial.println(str);

  str = String("Low Lmt : " + String(_aiParam->lowLimit));
  Serial.println(str);

  str = String("AlfaEma : " + String(_aiParam->alfaEma));
  Serial.println(str);

}

int AnalogInput::getStatus(){
    int sts = NORMAL;
    if (_aiParam->lowAlarm){
        sts = LOW_ALARM;
    }
    if (_aiParam->highAlarm){
        sts = HIGH_ALARM;
    }
    return sts;
}

//measure and putting in _aiParam
void AnalogInput::getValue(){
	unsigned long tempVal, pv;
		//calculate for EMA filter
		tempVal = (analogRead(_pin)*_aiParam->alfaEma + (100-_aiParam->alfaEma)*_PV_Raw)/100;

		_PV_Raw = tempVal;// after filtering
		pv = map(tempVal,0, 1023,_aiParam->lowRange , _aiParam->highRange);
    _aiParam->value = pv;
}
