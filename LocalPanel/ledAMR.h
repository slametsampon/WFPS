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

const int LED_READY = 0;
const int LED_AUTO = 1;
const int LED_MANUAL = 2;
const int LED_MANUAL_ON = 3;
const int LED_RESET = 4;
//const unsigned long DEBOUNCE_PB = 150;//milli second

#include "Arduino.h"
#include "src\digitalOutput\DigitalOutput.h"

    class LedAMR{
        public:
            LedAMR(DigitalOutput *ledAuto, DigitalOutput *ledManual, DigitalOutput *ledReset): _ledAuto(ledAuto), _ledManual(ledManual), _ledReset(ledReset){}
            
            void status(int state){
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

            void  info(){
                Serial.println("LedAMR::info()");
                String str;
                str = String("_ledAuto \n");//with new line
                str = String(str + _ledAuto->info());
                Serial.println(str);

                str = String("_ledManual \n");//with new line
                str = String(str + _ledManual->info());
                Serial.println(str);
                
                str = String("_ledReset \n");//with new line
                str = String(str + _ledReset->info());
                Serial.println(str);
                
            }
        private:
            DigitalOutput *_ledAuto, *_ledManual, *_ledReset;
    };

#endif
