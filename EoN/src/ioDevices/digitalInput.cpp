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

  if (typ == FORWARD_TYPE){
    pinMode(_pin, INPUT);
    _digTyp = FORWARD_TYPE;
  }
  else {
    pinMode(_pin, INPUT_PULLUP);
    _digTyp = REVERSE_TYPE;
  }
}

void DigitalInput::init(String id){
  _id = id;
  
  if (_digTyp == REVERSE_TYPE)pinMode(_pin, INPUT_PULLUP);

  else pinMode(_pin, INPUT);
}

boolean DigitalInput::isStatus(){

  if (_digTyp == REVERSE_TYPE)return (!digitalRead(_pin));

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

void DigitalInput::info(){

  Serial.print("Device : ");
  Serial.println(_id);

  Serial.print("Pin : ");
  Serial.println(_pin);

  Serial.print("Value : ");
  if (this->isStatus()) Serial.println("On");
  else Serial.println("Off");

  Serial.println("");
}

