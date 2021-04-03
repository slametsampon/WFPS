/*
  pbAMR.h - Library for P/B Auto, Manual, Reset
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

PbAMR::PbAMR(DigitalInput *pbAuto, DigitalInput *pbManual, DigitalInput *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

int PbAMR::getCmd(unsigned long debounceTime){
    int cmd;
    if (_pbReset->isStatus(debounceTime)){
      if (_prevCmd == MODE_RESET) cmd = MODE_READY;//highest priority
      else if (_prevCmd == MODE_READY) cmd = MODE_READY;//highest priority
      else cmd = MODE_RESET;//highest priority
      if(_prevCmd != cmd) _isInfo = false;
      _prevCmd = cmd;
    }
    else {
        if((_pbAuto->isStatus(debounceTime) && (_prevCmd != MODE_MANUAL_ON))){
            cmd = MODE_AUTO;//lower priority
            if(_prevCmd != cmd) _isInfo = false;
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(debounceTime)){
          if (_prevCmd == MODE_MANUAL) cmd = MODE_MANUAL_ON;//higher priority
          else if (_prevCmd == MODE_MANUAL_ON) cmd = MODE_MANUAL_ON;//higher priority
          else cmd = MODE_MANUAL;//higher priority

          if(_prevCmd != cmd) _isInfo = false;
          _prevCmd = cmd;
        }
        else cmd = _prevCmd;
    }
    return cmd;
}

String PbAMR::status(){
    String str = "NO_PB";
    switch (_prevCmd)
    {
    case MODE_AUTO:
        str = "PB : Auto";
        break;
    
    case MODE_MANUAL:
        str = "PB : Manual";
        break;
    
    case MODE_MANUAL_ON:
        str = "PB : Manual ON";
        break;
    
    case MODE_READY:
        str = "PB : Ready";
        break;
    
    case MODE_RESET:
        str = "PB : Reset";
        break;
    
    default:
        break;
    }
    return str;
}

void PbAMR::info(){
    Serial.println("PbAMR::info()");
    String str;

    Serial.println("_pbAuto");
    _pbAuto->info();
    Serial.println(str);

    Serial.println("_pbManual");
    _pbManual->info();
    
    Serial.println("_pbReset");
    _pbReset->info();
    
    Serial.println("<----->");
}
