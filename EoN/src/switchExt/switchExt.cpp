/*
  switchExt.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "switchExt.h"

SwitchExt::SwitchExt(int pin):_pin(pin){}
void SwitchExt::init(){
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. 
  // HARDWARE WIRING SHOULD BE CONCERNED !!!!! 
  pinMode(_pin, INPUT_PULLUP);
  _id = "SwitchExt";
}

boolean SwitchExt::isStatus(unsigned long holdTime){
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

String SwitchExt::info(){
  String str;
  str = String("Device : " + _id);
  str = String(str + "\n");//new line

  str = String(str + "Pin : ");
  str = String(str + _pin);
  str = String(str + "\n");//new line

  str = String(str + "Value : ");
  if (digitalRead(_pin)) str = String(str + "On");
  else str = String(str + "Off");

  return str;
}

