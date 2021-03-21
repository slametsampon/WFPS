/*
  analogInput.h - Library untuk AnalogInput
  Dibuat Oleh : Sam March 02, 2021
*/
#ifndef analogInput_h
#define analogInput_h

#include "Arduino.h"
#include "param.h"

    class AnalogInput{
        public:
            AnalogInput(char);
            void init(String);
            void setParameter(param*);
            param *getParameter();
            int getStatus();
            String toString();
            void info();
            void getValue();
        private:
            param   *_param;
            char _pin;
            unsigned int _PV_Raw;
            String _id;//
    };

#endif