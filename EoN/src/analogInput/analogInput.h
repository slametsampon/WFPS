/*
  analogInput.h - Library untuk AnalogInput
  Dibuat Oleh : Sam March 02, 2021
*/
#ifndef analogInput_h
#define analogInput_h

#include "Arduino.h"
#include "aiParam.h"

const int AI_NORMAL = 0;
const int AI_HIGH_ALARM = 1;
const int AI_LOW_ALARM = 2;

    class AnalogInput{
        public:
            AnalogInput(char);
            void init(String);
            void setParameter(aiParam*);
            aiParam *getParameter();
            int getStatus();
            String toString();
            void info();
            void getValue();
        private:
            aiParam   *_aiParam;
            char _pin;
            unsigned int _PV_Raw;
            String _id;//
    };

#endif