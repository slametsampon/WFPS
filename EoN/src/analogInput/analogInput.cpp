/*
  fireSensor.h - Library untuk AnalogInput
  Dibuat Oleh : Sam March 02, 2021
*/

#include    "analogInput.h"

AnalogInput::AnalogInput(char pin):_pin(pin){}

void AnalogInput::init(String id){
  _id = id;
}

void AnalogInput::setParameter(param *dtParam){
    _param = dtParam;
}

param *AnalogInput::getParameter(){
    return _param;
}

String AnalogInput::toString(){
  String str = _id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + _param->unit);
  if (_param->alarm == LOW_ALARM){
    alm = "(L)";
  }
  if (_param->alarm == HIGH_ALARM){
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

  str = String("Unit : " + _param->unit);
  Serial.println(str);

  str = String("High Range : " + String(_param->highRange));
  Serial.println(str);

  str = String("Low Range : " + String(_param->lowRange));
  Serial.println(str);

  str = String("High Limit : "+ String(_param->highLimit));
  Serial.println(str);

  str = String("Low Lmt : " + String(_param->lowLimit));
  Serial.println(str);

  str = String("AlfaEma : " + String(_param->alfaEma));
  Serial.println(str);

}

int AnalogInput::getStatus(){
    return _param->alarm;
}

//measure and putting in _param
void AnalogInput::getValue(){
	unsigned long tempVal, pv;
		//calculate for EMA filter
		tempVal = (analogRead(_pin)*_param->alfaEma + (100-_param->alfaEma)*_PV_Raw)/100;

		_PV_Raw = tempVal;// after filtering
		pv = map(tempVal,0, 1023,_param->lowRange , _param->highRange);

    _param->value = pv;
    _param->alarm = NO_ALARM;
    if (pv >= _param->highLimit)_param->alarm = HIGH_ALARM;
    else if (pv <= _param->lowLimit)_param->alarm = LOW_ALARM;
}
