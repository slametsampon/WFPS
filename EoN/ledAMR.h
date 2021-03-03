/*
  ledAMR.h - Library for LED Auto, Manual, Reset
  By : Sam March 01, 2021

  1. LED_READY = all LED off
  2. LED_AUTO = LED Auto on, others off
  3. LED_MANUAL = LED Manual on, others off
  4. LED_MANUAL_ON = LED Manual blink, others off
  5. LED_RESET = LED Reset on, others off
*/

#ifndef ledAMR_h
#define ledAMR_h

const char LED_READY = 0;
const char LED_AUTO = 1;
const char LED_MANUAL = 2;
const char LED_MANUAL_ON = 3;
const char LED_RESET = 4;
//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "src\ledExt\ledExt.h"

    class LedAMR{
        public:
            LedAMR(LedExt *ledAuto, LedExt *ledManual, LedExt *ledReset): _ledAuto(ledAuto), _ledManual(ledManual), _ledReset(ledReset){}
            void info(char state){
                switch (state){
                case LED_AUTO:
                    _ledAuto->on();
                    _ledManual->off();
                    _ledReset->off();
                    break;
                
                case LED_MANUAL:
                    _ledManual->on();
                    _ledAuto->off();
                    _ledReset->off();
                    break;
                
                case LED_MANUAL_ON:
                    _ledManual->blink(250);
                    _ledAuto->off();
                    _ledReset->off();
                    break;
                
                case LED_READY:
                    _ledAuto->off();
                    _ledManual->off();
                    _ledReset->off();
                    break;
                
                case LED_RESET:
                    _ledReset->on();
                    _ledAuto->off();
                    _ledReset->off();
                    break;
                
                default:
                    break;
                }
            }
        private:
            LedExt *_ledAuto, *_ledManual, *_ledReset;
    };

#endif
