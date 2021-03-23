/*
 * lihat header file DigitalOutput.h lebih detail
 * Digital Input with debouncing mechanism 
 * extention file harus .cpp bukan .CPP
 */

/* Dependencies */
#include "DigitalOutput.h"

DigitalOutput::DigitalOutput(int pin):_pin(pin){}

void DigitalOutput::init(boolean actType){
  pinMode(_pin, OUTPUT);

  _id = "Digital Output";
  _actionType = actType;
}

void DigitalOutput::init(String id){
  pinMode(_pin, OUTPUT);

  _id = id;
  _actionType = FORWARD_DO;
}

void DigitalOutput::init(boolean actType, String id){
  pinMode(_pin, OUTPUT);

  _id = id;
  _actionType = actType;
}

void DigitalOutput::on(){
  if (_actionType == FORWARD_DO) digitalWrite(_pin, HIGH);
  else digitalWrite(_pin, LOW);
}

void DigitalOutput::off(){
  if (_actionType == FORWARD_DO) digitalWrite(_pin, LOW);
  else digitalWrite(_pin, HIGH);
}

void DigitalOutput::blink(unsigned long blinkTime){
    if ((millis() - _prevMilli) >= blinkTime){
        _prevMilli = millis();
        digitalWrite( _pin, digitalRead(_pin) ^ 1 );
    }
}

String DigitalOutput::info(){
  String str;
  str = String("Device : " + _id);
  str = String(str + "\n");//new line

  str = String(str + "Pin : ");
  str = String(str + _pin);
  str = String(str + "\n");//new line

  str = String(str + "Action : ");
  if (_actionType == FORWARD_DO) str = String(str + "FORWARD");
  else str = String(str + "REVERSE");
  str = String(str + "\n");//new line

  str = String(str + "Value : ");
  if (digitalRead(_pin)) str = String(str + "On\n");
  else str = String(str + "Off\n");

  return str;
}
