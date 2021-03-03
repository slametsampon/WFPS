/*
  pbAMR.h - Library for P/B Auto, Manual, Reset
  By : Sam March 01, 2021
*/

/* Dependencies */
#include "pbAMR.h"

PbAMR::PbAMR(SwitchExt *pbAuto, SwitchExt *pbManual, SwitchExt *pbReset): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset){}

char PbAMR::getCmd(unsigned long debounceTime){
    char cmd;
    if (_pbReset->isStatus(debounceTime)){
      if (_prevCmd == PB_RESET) cmd = PB_READY;//highest priority
      else if (_prevCmd == PB_READY) cmd = PB_READY;//highest priority
      else cmd = PB_RESET;//highest priority
      if(_prevCmd != cmd) _isInfo = false;
      _prevCmd = cmd;
    }
    else {
        if((_pbAuto->isStatus(debounceTime) && (_prevCmd != PB_MANUAL_ON))){
            cmd = PB_AUTO;//lower priority
            if(_prevCmd != cmd) _isInfo = false;
            _prevCmd = cmd;
        }
        if(_pbManual->isStatus(debounceTime)){
          if (_prevCmd == PB_MANUAL) cmd = PB_MANUAL_ON;//higher priority
          else if (_prevCmd == PB_MANUAL_ON) cmd = PB_MANUAL_ON;//higher priority
          else cmd = PB_MANUAL;//higher priority

          if(_prevCmd != cmd) _isInfo = false;
          _prevCmd = cmd;
        }
        else cmd = _prevCmd;
    }
    return cmd;
}

void PbAMR::info(){
    if(!_isInfo){
        _isInfo = true;
        switch (_prevCmd)
        {
        case PB_AUTO:
            Serial.println("PB : Auto");
            break;
        
        case PB_MANUAL:
            Serial.println("PB : Manual");
            break;
        
        case PB_MANUAL_ON:
            Serial.println("PB : Manual ON");
            break;
        
        case PB_READY:
            Serial.println("PB : Ready");
            break;
        
        case PB_RESET:
            Serial.println("PB : Reset");
            break;
        
        default:
            break;
        }
    }
}