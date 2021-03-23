/*
  keyPad.h - Library untuk keyPad
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef keyPad_h
#define keyPad_h

#include "Arduino.h"
#include "src\command\command.h"

const int DEBOUNCE_DELAY = 150;//milli second

class KeyPad : public command{
  public:
    KeyPad(int);//constructor
    void Init();//Initialization
    int ambilNilai();//function for getting keypad value
    char ambilCode();//Convert keypad value to char
  private:
    int _pinAnalog;
    unsigned long _prevMilli;
    char _prevKey;
};//end of class
#endif
