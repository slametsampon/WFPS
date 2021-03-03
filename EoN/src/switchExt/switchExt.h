/*
  switchExt.h - Library for Switch Extended
  Switch with debouncing mechanism 
  By : Sam March 01, 2021
*/

#ifndef switchExt_h
#define switchExt_h

#include "Arduino.h"

    //master/base class
    class Device{
        public:
            virtual void init();
            virtual boolean isStatus(unsigned long);
        private:
    };

    class SwitchExt : public Device{
        public: 
            SwitchExt(int pin);   
            void init();
            boolean isStatus(unsigned long);
            String info();
        private:
            int  _pin;
            unsigned long  _prevMilli;
            String  _id;
    };
#endif
