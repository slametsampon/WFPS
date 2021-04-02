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
  _actionType = FORWARD_TYPE;
}

void DigitalOutput::init(boolean actType, String id){
  pinMode(_pin, OUTPUT);

  _id = id;
  _actionType = actType;
}

boolean DigitalOutput::isStatus(){

  if (_actionType == REVERSE_TYPE)return (!digitalRead(_pin));

  else return (digitalRead(_pin));
  
}

void DigitalOutput::on(){
  if (_actionType == FORWARD_TYPE) digitalWrite(_pin, HIGH);
  else digitalWrite(_pin, LOW);
}

void DigitalOutput::off(){
  if (_actionType == FORWARD_TYPE) digitalWrite(_pin, LOW);
  else digitalWrite(_pin, HIGH);
}

void DigitalOutput::blink(unsigned long blinkTime){
    if ((millis() - _prevMilli) >= blinkTime){
        _prevMilli = millis();
        digitalWrite( _pin, digitalRead(_pin) ^ 1 );
    }
}

void DigitalOutput::info(){
  Serial.print("Device : ");
  Serial.println(_id);

  Serial.print("Pin : ");
  Serial.println(_pin);

  Serial.print("Action : ");
  if (_actionType == FORWARD_TYPE) Serial.println("FORWARD");
  else Serial.println("REVERSE");

  Serial.print("Value : ");
  if (this->isStatus()) Serial.println("On");
  else Serial.println("Off");

}
