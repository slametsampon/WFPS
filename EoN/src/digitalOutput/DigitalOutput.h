/*
  digitalOutput.h - Library for Digital Output (DO)
  Digital Input with debouncing mechanism 
  By : Sam March 03, 2021
*/

#ifndef DigitalOutput_h
#define DigitalOutput_h

#include "Arduino.h"

const boolean FORWARD_DO= true;
const boolean REVERSE_DO= false;


  class DigitalOutput{
    public: 
      //constructor
      DigitalOutput(int pin);  

      //from deviceBase.h 
      void init(boolean);
      String info();

      //typical for DO
      void on();
      void off();
      //void blink(unsigned long);
    private:
      int  _pin;
      String _id;
      unsigned long  _prevMilli;
      boolean _actionType;
  };
#endif
