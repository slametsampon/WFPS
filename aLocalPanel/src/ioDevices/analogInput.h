/*
  analogInput.h - Library AI
  with AlfaEma filter
  By : Sam April 03, 2021
*/

#ifndef analogInput_h
#define analogInput_h

#include "Arduino.h"
#include "signalConst.h"

    class AnalogInput{
        public: 
            AnalogInput(int pin);   
            void init(boolean);
            void init(String);
            int getValue(int);
            int getRaw();
            void info();
        private:
            int  _pin, _prevVal;
            String  _id;
            boolean _pullUp;
    };
#endif
