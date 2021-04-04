/*
  analogInput.h - Library AI
  with AlfaEma filter
  By : Sam April 03, 2021
*/

#ifndef analogInput_h
#define analogInput_h

#include "Arduino.h"
#include "signalConst.h"
#include "param.h"

    class AnalogInput{
        public: 
            AnalogInput(int pin);   
            void init(boolean);
            void init(String);
            int getRaw();
            float getValue();
            int getStatus();
            void attachModelParameter(AccessParam*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
            void info();
        private:
            int  _pin, _prevVal;
            String  _id;
            boolean _pullUp;
            param _dataParam;
            AccessParam *_accessParameter;
    };
#endif
