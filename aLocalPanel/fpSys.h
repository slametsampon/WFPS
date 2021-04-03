/*
  FPSys.h - Library for Fire Protection System
  By : Sam March 03, 2021

*/

#ifndef FPSys_h
#define FPSys_h

//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "src\compDevices\ledAMR.h"
#include "src\compDevices\pbAMRT.h"
#include "src\ioDevices\analogInput.h"
#include "src\global\localPanelConst.h"

    class FPSys{
        
        public:
            FPSys(String);
            void info();
            void attachLedAMR(LedAMR*);
            void attachPbAMRT(PbAMRT*);
            void attachFireSensor(AnalogInput*);
            void attachSolenoidValve(DigitalOutput*);
            void execute();

        private:
            String  _id;

            LedAMR *_ledAMR;
            PbAMRT *_pbAMRT;
            AnalogInput *_fireSensor;
            DigitalOutput   *_solenoidValve;

            int _operationMode;
            int _getInput();
    };

#endif
