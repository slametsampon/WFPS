/*
  dipAddr.h - Library for Addressing
  Addres  :
    0. 000
    1. 001
    .....
    7. 111
  By : Sam March 18, 2021
*/

#ifndef dipAddr_h
#define dipAddr_h

#include "Arduino.h"
#include "src\switchExt\switchExt.h"

    class DipAddr{
        public:
            DipAddr(SwitchExt*, SwitchExt*, SwitchExt*);
            int getAddr();
            void info();
        private:
            SwitchExt *_addr0, *_addr1, *_addr2;
    };

#endif
