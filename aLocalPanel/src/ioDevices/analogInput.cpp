/*
  analogInput.h - Library AI
  with AlfaEma filter
  By : Sam April 03, 2021
*/

/* Dependencies */
#include "analogInput.h"

AnalogInput::AnalogInput(int pin):_pin(pin){
    _id = "AnalogInput";
    pinMode(_pin, INPUT);
}

void AnalogInput::init(boolean typ){
  if (typ == PULLUP){
    pinMode(_pin, INPUT_PULLUP);
    _pullUp = PULLUP;
  }
  else {
    pinMode(_pin, INPUT);
  }
}

void AnalogInput::init(String id){
  _id = id;
  
}

void AnalogInput::attachModelParameter(AccessParam *accessParameter){
    Serial.println("AnalogInput::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
 
int AnalogInput::getRaw(){
    return analogRead(_pin);

}

float AnalogInput::getValue(){

  _dataParam = _accessParameter->getParam();
  
  float inMin = 0.0;
  float inMax = 1023.0;

  //calculate for EMA filter
  float facCurrent = _dataParam.alfaEma/100.0;
  float facPrev = (100.0 - _dataParam.alfaEma)/100.0;
  int raw = this->getRaw();

  float tempVal = raw * facCurrent + facPrev * _prevVal;

  //convert to unit
  float valUnit = (tempVal - inMin) * (_dataParam.highRange - _dataParam.lowRange) / (inMax - inMin) + _dataParam.lowRange;

  //report by exception
  if (_dataParam.value != valUnit){
    //save to parameter
    _accessParameter->setValue(valUnit);

    Serial.print("valUnit : ");
    Serial.println(valUnit);

    Serial.print("_dataParam.value : ");
    Serial.println(_dataParam.value);

  }
  return valUnit;
}

int AnalogInput::getStatus(){
  int statusAi = NO_ALARM;

  float valUnit = this->getValue();

  if (valUnit <= _dataParam.lowLimit)statusAi = LOW_ALARM;
  else if (valUnit >= _dataParam.highLimit)statusAi = HIGH_ALARM;

  if (_dataParam.alarm != statusAi){
    //save to parameter
    _accessParameter->setAlarm(statusAi);

    Serial.print("statusAi : ");
    Serial.println(statusAi);

    _accessParameter->info();
  }

  return statusAi;
}

void AnalogInput::info(){

  Serial.print("Device : ");
  Serial.println(_id);

  Serial.print("Pin : ");
  Serial.println(_pin);

  Serial.print("PullUp : ");
  Serial.println(_pullUp);

  Serial.print("getRaw() : ");
  Serial.println(this->getRaw());

  Serial.println("");
}

