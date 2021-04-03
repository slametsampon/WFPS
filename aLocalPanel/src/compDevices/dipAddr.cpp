/*
  dipAddr.h - Library for Addressing
  Addres  :
    0. 000
    1. 001
    .....
    7. 111
  By : Sam March 18, 2021
*/

/* Dependencies */
#include "dipAddr.h"

DipAddr::DipAddr(DigitalInput *addr0, DigitalInput *addr1, DigitalInput *addr2): _addr0(addr0), _addr1(addr1), _addr2(addr2){}

int DipAddr::getAddr(){
    int addr = 0;
    if (_addr0->isStatus()) addr += 1;
    if (_addr1->isStatus()) addr += 2;
    if (_addr2->isStatus()) addr += 4;
    return (addr);
}

void DipAddr::info(){
    Serial.println("DipAddr::info()");
    
    Serial.println("_addr0");
    _addr0->info();

    Serial.println("_addr1");
    _addr1->info();
    
    Serial.println("_addr2");
    _addr2->info();
    
    Serial.print("Address : ");
    Serial.println(this->getAddr());
    Serial.println("<----->");
}
