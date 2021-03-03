/*
  LedExtExt.cpp (not .CPP - upper case)
  LedExt with multiple functionality (on, off, blink)
  By : Sam March 01, 2021
*/
#include "arduino.h"
#include "ledExt.h"

LedExt::LedExt(int pin):_pin(pin){}

void LedExt::init(){
    pinMode(_pin, OUTPUT);
    _id = "LedExt";
}

void LedExt::on(){
    digitalWrite(_pin, HIGH);//reverse due to pull up
}

void LedExt::off(){
    digitalWrite(_pin, LOW);//reverse due to pull up
}

void LedExt::blink(unsigned long blinkTime){
    if ((millis() - _prevMilli) >= blinkTime){
        _prevMilli = millis();
        digitalWrite( _pin, digitalRead(_pin) ^ 1 );
    }
}

String LedExt::info(){
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

