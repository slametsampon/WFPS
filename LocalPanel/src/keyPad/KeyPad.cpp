/*
 * lihat header file KeyPad.h lebih detail
 * extention file harus .cpp bukan .CPP
 * Feb 13, 2021 by Sam
 */

/* Dependencies */
#include "keyPad.h"

KeyPad::KeyPad(int pin):_pinAnalog(pin){
  //pinMode(_pinAnalog, INPUT_PULLUP);  // set pull-up on analog pin
  this->_prevKey = NO_KEY;
}

void KeyPad::info(){
    Serial.println("KeyPad::info()");
    String str;

    str = String("_pinAnalog : " + _pinAnalog);
    Serial.println(str);

    str = String("VALUE_UP : " + VALUE_UP);
    Serial.println(str);

    str = String("VALUE_DOWN : " + VALUE_DOWN);
    Serial.println(str);

    str = String("VALUE_LEFT : " + VALUE_LEFT);
    Serial.println(str);

    str = String("VALUE_SELECT : " + VALUE_SELECT);
    Serial.println(str);
}

void KeyPad::init(){}

//function for getting keypad value
int KeyPad::getValue(){
      int keyVal = analogRead(_pinAnalog);
      return keyVal;
  }

bool KeyPad::isValid(char cmdVal){
  bool flVal = false;
  switch (cmdVal){
    
    //Keypad validation
    case UP: 
    case DOWN:
    case RIGHT:
    case LEFT:
    case SELECT:
      flVal = true;
      break;
    
    //Other validation bluetooth, esp etc...
    default:
      break;
  }
  return flVal;
}

//Convert keypad value to char with debouncing mechanism
char KeyPad::getCode(){
      int key = getValue();
      char keyPad = NO_KEY;//Default key, No key
      char keyReturn = NO_KEY;//Default key, No key
      if (key < VALUE_RIGHT) {
        keyPad =  RIGHT;
      }
      else if (key < VALUE_UP) {
        keyPad = UP;
      }
      else if (key < VALUE_DOWN){
        keyPad = DOWN;
      }
      else if (key < VALUE_LEFT){
        keyPad = LEFT;
      }
      else if (key < VALUE_SELECT){
        keyPad = SELECT;
      }
      
      //debouncing mechanism
      if (this->_prevKey != keyPad){
        this->_prevMilli = millis();
        this->_prevKey = keyPad;
      }

      else {
        if ((millis() - this->_prevMilli) > DEBOUNCE_DELAY){
          this->_prevMilli = millis();
          this->_prevKey = keyPad;
          keyReturn = keyPad;
        }
      }
    return keyReturn;
  }  
