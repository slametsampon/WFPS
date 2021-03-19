/*
  fireSensor.h - Library untuk AnalogInput
  Dibuat Oleh : Sam March 02, 2021
*/

#include    "analogInput.h"

AnalogInput::AnalogInput(char pin):_pin(pin){}

void AnalogInput::init(String id){
  _id = id;
}

void AnalogInput::setParameter(aiParam *param){
    _aiParam = param;
}

aiParam *AnalogInput::getParameter(){
    return _aiParam;
}

String AnalogInput::toString(){
  String str = _id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + _aiParam->unit);
  if (_aiParam->alarm == AI_LOW_ALARM){
    alm = "(L)";
  }
  if (_aiParam->alarm == AI_HIGH_ALARM){
    alm = "(H)";
  }
  str =  String(str + alm);
  return str;
}

void AnalogInput::info(){
  String str;
  str = String("Device : " + _id);
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
    return _aiParam->alarm;
}

//measure and putting in _aiParam
void AnalogInput::getValue(){
	unsigned long tempVal, pv;
		//calculate for EMA filter
		tempVal = (analogRead(_pin)*_aiParam->alfaEma + (100-_aiParam->alfaEma)*_PV_Raw)/100;

		_PV_Raw = tempVal;// after filtering
		pv = map(tempVal,0, 1023,_aiParam->lowRange , _aiParam->highRange);

    _aiParam->value = pv;
    _aiParam->alarm = AI_NORMAL;
    if (pv >= _aiParam->highLimit)_aiParam->alarm = AI_HIGH_ALARM;
    else if (pv <= _aiParam->lowLimit)_aiParam->alarm = AI_LOW_ALARM;
}
