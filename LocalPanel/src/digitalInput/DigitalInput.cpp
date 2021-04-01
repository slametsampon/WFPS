/*
  digitalInput.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "digitalInput.h"

DigitalInput::DigitalInput(int pin):_pin(pin){}

void DigitalInput::init(boolean typ){
  _id = "DigitalInput";

  if (typ == FORWARD_DI){
    pinMode(_pin, INPUT);
    _digTyp = FORWARD_DI;
  }
  else {
    pinMode(_pin, INPUT_PULLUP);
    _digTyp = REVERSE_DI;
  }
}

void DigitalInput::init(String id){
  _id = id;
  
  if (_digTyp == REVERSE_DI)pinMode(_pin, INPUT_PULLUP);

  else pinMode(_pin, INPUT);
}

boolean DigitalInput::isStatus(){

  if (_digTyp == REVERSE_DI)return (!digitalRead(_pin));

  else return (digitalRead(_pin));
  
}

boolean DigitalInput::isStatus(unsigned long holdTime){
  boolean validSts = false;

  if (this->isStatus()){
    if (_prevMilli == 0){
      _prevMilli = millis();//Transition for new command
    }
    else {
      if ((millis() - _prevMilli) >= holdTime){
        validSts = true;
        _prevMilli = 0;
      }
    }
  }
  return validSts;
}

String DigitalInput::info(){
  String str;
  str = String("Device : " + _id);
  str = String(str + "\n");//new line

  str = String(str + "Pin : ");
  str = String(str + _pin);
  str = String(str + "\n");//new line

  str = String(str + "Value : ");
  if (digitalRead(_pin)) str = String(str + "On \n");//with new line
  else str = String(str + "Off \n");//with new line

  return str;
}

