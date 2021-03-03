/*
 * lihat header file DigitalInput.h lebih detail
 * Digital Input with debouncing mechanism 
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "digitalInput.h"

DigitalInput::DigitalInput(int pin):_pin(pin){}

void DigitalInput::init(boolean actTyp){
  _isSimulate = false;
  _id = "Digital Input";
  _prevMilli = 0;
  _actionType = actTyp;
  this->_setActionType(_actionType);
}

void DigitalInput::_setActionType(boolean actType){
  _actionType = actType;
  if (actType == FORWARD_DI) pinMode(_pin, INPUT);
  else pinMode(_pin, INPUT_PULLUP);//High = Open, Low = close
}

boolean DigitalInput::isSimulate(){
    return _isSimulate;
}

void DigitalInput::setSimulate(boolean simVal){
    _isSimulate = simVal;
}

boolean DigitalInput::getValue(){
  boolean val;
    if (_isSimulate) val = _valSimulate;
    else{
      if (_actionType == FORWARD_DI) val = digitalRead(_pin);
      else val = !digitalRead(_pin);//Reverse action
    }
  return val;
}

//with debouncing mechanism
boolean DigitalInput::getValue(unsigned long holdTime){
  boolean validSts = false;
  if (this->getValue()){
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

  str = String(str + "Action : ");
  if (_actionType == FORWARD_DI) str = String(str + "FORWARD");
  else str = String(str + "REVERSE");
  str = String(str + "\n");//new line

  str = String(str + "Simulate : ");
  if (_isSimulate) str = String(str + "True");
  else str = String(str + "False");
  str = String(str + "\n");//new line

  str = String(str + "Value : ");
  if (this->getValue()) str = String(str + "Close");
  else str = String(str + "Open");

  return str;
}
