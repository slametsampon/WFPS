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
#include "src\model\model.h"

    class FPSys{
        
        public:
            FPSys(String);
            void init();
            void info();
            void attachLedAMR(LedAMR*);
            void attachPbAMRT(PbAMRT*);
            void attachFireSensor(AnalogInput*);
            void attachSolenoidValve(DigitalOutput*);
            void attachBuzzer(DigitalOutput*);
            void attachModelParameter(AccessParam*);//Pasang Model parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
            int getException();
            void updateParameter();
            void execute();

        private:
            String  _id;
            int _exception = NO_EXCEPTION;

            LedAMR *_ledAMR;
            PbAMRT *_pbAMRT;
            AnalogInput *_fireSensor;
            DigitalOutput   *_solenoidValve, *_buzzer;
            AccessParam *_accessParameter;
            param _dataParam;

            boolean _getSensorStatus();
            void _logicOperation(int, int);
    };

#endif
