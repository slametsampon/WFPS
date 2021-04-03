/*
  pbAMRT.h - Library for P/B Auto, Manual, Reset, Test
  By : Sam April 03, 2021
*/

/* Dependencies */
#include "pbAMRT.h"

PbAMRT::PbAMRT(DigitalInput *pbAuto, DigitalInput *pbManual, DigitalInput *pbReset, DigitalInput *pbTest): _pbAuto(pbAuto), _pbManual(pbManual), _pbReset(pbReset), _pbTest(pbTest){}

int PbAMRT::getCmd(unsigned long debounceTime){
    int cmd;

    //mode test is top priority
    if (_pbTest->isStatus(debounceTime)){
        cmd = MODE_TEST;
        _prevCmd = cmd;
        return cmd;
    }

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

String PbAMRT::status(){
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
    
    case MODE_TEST:
        str = "PB : Test";
        break;
    
    default:
        break;
    }
    return str;
}

void PbAMRT::info(){
    Serial.println("PbAMRT::info()");
    String str;

    Serial.println("_pbAuto");
    _pbAuto->info();
    Serial.println(str);

    Serial.println("_pbManual");
    _pbManual->info();
    
    Serial.println("_pbReset");
    _pbReset->info();
    
    Serial.println("_pbTest");
    _pbTest->info();
    
    Serial.println("<----->");
}
