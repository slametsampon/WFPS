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

int AnalogInput::getRaw(){
    return analogRead(_pin);

}

int AnalogInput::getValue(int alfaEma){
	unsigned long tempVal;
    //calculate for EMA filter
    tempVal = (this->getRaw() * alfaEma + (100-alfaEma)*_prevVal)/100;

    _prevVal = (int) tempVal;// after filtering
}
void AnalogInput::info(){

  Serial.print("Device : ");
  Serial.println(_id);

  Serial.print("Pin : ");
  Serial.println(_pin);

  Serial.print("PullUp : ");
  Serial.println(_pullUp);

  Serial.print("Value : ");
  Serial.println(this->getRaw());

  Serial.println("");
}

