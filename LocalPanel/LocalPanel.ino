/*
Arduino 2x16 LCD - test program
modified on 28 Feb 2021, for OOP and MVC
*/

#include <LiquidCrystal.h>//for LCD
#include <RTClib.h>

//Library yang dibuat sendiri lihat file KeyPad.h dan KeyPad.cpp
#include "SequenceTimer.h"
#include "Model.h"//part of MVC pattern, see Model.h
#include "View.h"//part of MVC pattern, see View.h
#include "Controller.h"//part of MVC pattern, see Controller.h

/*
LCD pin setting
For LCD Keypad DF Robot
*/
#define PIN_KEYPAD A0 // pin Analog Keypad

const int LCD_RS = 8;
const int LCD_EN = 9;
const int LCD_D4 = 4;
const int LCD_D5 = 5;
const int LCD_D6 = 6;
const int LCD_D7 = 7;

RTC_Millis rtc;//software RTC

//Variables declaration
LiquidCrystal   lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
KeyPad          keyPad(PIN_KEYPAD);//declare keypad
serialCmd       serInput("Serial Command");
View            view(lcd);//declare view, part of MVC pattern
SequenceTimer   sequenceUtama("Sequence");
AccessDataMenu  accessMenuUtama("Data Menu");//part of MVC pattern
AccessParameter accessParameter("Parameter");//part of MVC pattern
Controller      controller("Controller");//part of MVC pattern
DateTime        waktuSekarang;//mencatat waktu sekarang
String          waktu;

//Static member class should be initialized FIRST (IF NOT, WILL HAVE ERROR)
unsigned char Controller::cmdInNbr=0;
unsigned char AccessDataMenu::menuNbr=0;
unsigned char AccessParameter::paramNbr=0;


//function declaration
void setupParameter();
void setupMenuUtama();

