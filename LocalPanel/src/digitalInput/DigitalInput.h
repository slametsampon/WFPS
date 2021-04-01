/*
  digitalInput.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

#ifndef digitalInput_h
#define digitalInput_h

#include "Arduino.h"
const boolean FORWARD_DI = true;
const boolean REVERSE_DI = false;

    class DigitalInput{
        public: 
            DigitalInput(int pin);   
            void init(boolean);
            void init(String);
            boolean isStatus(unsigned long);
            boolean isStatus();
            String info();
        private:
            int  _pin;
            unsigned long  _prevMilli;
            String  _id;
            boolean _digTyp = REVERSE_DI;
    };
#endif
