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
#include "..\global\localPanelConst.h"

    class AnalogInput{
        public: 
            AnalogInput(int pin);   
            void init(boolean);
            void init(String);
            int getRaw();
            float getValue();
            int getStatus();
            int getException();
            void attachModelParameter(AccessParam*);//penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
            void info();
        private:
            int _exception = NO_EXCEPTION;
            int  _pin, _prevVal;
            String  _id;
            boolean _pullUp;
            param _dataParam;
            AccessParam *_accessParameter;
    };
#endif
