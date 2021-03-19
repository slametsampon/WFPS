/*
  analogInput.h - Library untuk AnalogInput
  Dibuat Oleh : Sam March 02, 2021
*/
#ifndef analogInput_h
#define analogInput_h

#include "Arduino.h"

const int NORMAL = 0;
const int HIGH_ALARM = 1;
const int LOW_ALARM = 2;

    typedef struct aiParam{
        String id;//
        String unit;//unit
        float value;
        float highRange;
        float lowRange;
        float highLimit;//for alarm high
        float lowLimit;//for alarm low
        unsigned int alfaEma;//alfa for EMA Filter (0 - 100) in percentage
        boolean highAlarm = false;
        boolean lowAlarm = false;
    }aiParam;

    class AnalogInput{
        public:
            AnalogInput(char);
            void Init();
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
    };

#endif