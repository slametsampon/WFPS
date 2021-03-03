/*
  digitalInput.h - Library for Digital Input (DI)
  Digital Input with debouncing mechanism 
  By : Sam March 03, 2021
*/

#ifndef DigitalInput_h
#define DigitalInput_h

#include "Arduino.h"
const boolean FORWARD_DI = true;
const boolean REVERSE_DI = false;


  class DigitalInput{
    public: 
      //constructor
      DigitalInput(int pin);  

      void init(boolean);
      String info();
      void setSimulate(boolean);
      boolean isSimulate();
      void setSimulateValue(boolean);
      boolean getValue();
      boolean getValue(unsigned long);
    private:
      int  _pin;
      String _id;
      unsigned long  _prevMilli;
      boolean _actionType;
      boolean _isSimulate, _valSimulate;    
      void _setActionType(boolean);
  };
#endif
