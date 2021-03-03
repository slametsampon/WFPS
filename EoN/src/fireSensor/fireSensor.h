/*
  fireSensor.h - Library untuk FireSensor
  Dibuat Oleh : Sam March 02, 2021
*/
#ifndef fireSensor_h
#define fireSensor_h

#include "Arduino.h"

const char NORMAL = 0;
const char HIGH_ALARM = 1;
const char LOW_ALARM = 2;

    typedef struct sensorParam{
        String id;//
        String unit;//unit
        float value;
        float raw;
        float highRange;
        float lowRange;
        float highLimit;//for alarm high
        float lowLimit;//for alarm low
        unsigned int alfaEma;//alfa for EMA Filter (0 - 100) in percentage
        boolean highAlarm = false;
        boolean lowAlarm = false;
    }sensorParam;

    class FireSensor{
        public:
            FireSensor(char);
            unsigned char Init();
            void setParameter(sensorParam*);
            sensorParam *getParameter();
            char getStatus();
            String toString();
            String info();
            float getValue();
        private:
            sensorParam   *_sensorParam;
            char _pin;
            unsigned int _PV_Raw;
    };

#endif