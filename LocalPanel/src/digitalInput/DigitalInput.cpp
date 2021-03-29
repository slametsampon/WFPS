/*
  digitalInput.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "digitalInput.h"

DigitalInput::DigitalInput(int pin):_pin(pin){}
void DigitalInput::init(boolean typ){
  if (typ == FORWARD_DI)pinMode(_pin, INPUT);
  else pinMode(_pin, INPUT_PULLUP);
  _id = "DigitalInput";
  _initTyp = true;
}

void DigitalInput::init(String id){
  if (!_initTyp)pinMode(_pin, INPUT_PULLUP);
  _id = id;
}

boolean DigitalInput::isStatus(){
  //HIGH when it's open, and LOW when it's pressed. it's INPUT_PULLUP
  return (!digitalRead(_pin));
}

boolean DigitalInput::isStatus(unsigned long holdTime){
  boolean validSts = false;
  //HIGH when it's open, and LOW when it's pressed. it's INPUT_PULLUP
  if (!digitalRead(_pin)){
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

