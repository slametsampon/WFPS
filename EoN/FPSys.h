/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/

#ifndef FPSys_h
#define FPSys_h

//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "ledAMR.h"
#include "pbAMR.h"
#include "src\fireSensor\fireSensor.h"
#include "src\digitalOutput\DigitalOutput.h"

    class FPSys{
        
        public:
            FPSys(String);
            void info();
            void attachLedAMR(LedAMR*);
            void attachPbAMR(PbAMR*);
            void attachFireSensor(FireSensor*);
            void attachSolenoidValve(DigitalOutput*);
            void execute();

        private:
            String  _id;

            LedAMR *_ledAMR;
            PbAMR *_pbAMR;
            FireSensor *_fireSensor;
            DigitalOutput   *_solenoidValve;

            int _operationMode;
            int _getInput();
    };

#endif
