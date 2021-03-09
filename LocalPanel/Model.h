/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
  JSON
{
  "id":"Smoke-1",
  "unit":"%",
  "indexMenu":1,
  "value":51.5,
  "highRange":100.0,
  "lowRange":0.0,
  "highLimit":80.0,
  "lowLimit":40.0,
  "increment":1.1
  }

StaticJsonDocument<96> doc;

doc["id"] = "Smoke-1";
doc["unit"] = "%";
doc["indexMenu"] = 1;
doc["value"] = 51.5;
doc["highRange"] = 100;
doc["lowRange"] = 0;
doc["highLimit"] = 80;
doc["lowLimit"] = 40;
doc["increment"] = 1.1;

serializeJson(doc, output);
*/
#ifndef Model_h
#define Model_h

#include "Arduino.h"

const int MAX_MENU = 10;
const int PARAMETER_VALUE = 0;
const int PARAMETER_LOW_RANGE = 1;
const int PARAMETER_HIGH_RANGE = 2;
const int PARAMETER_LOW_LIMIT = 3;
const int PARAMETER_HIGH_LIMIT = 4;
const int PARAMETER_INCREMENT = 5;
const float DELTA_INCREMENT = 0.1;

typedef struct parameter{
  String id;//
  String unit;//unit
  int indexMenu;//index menu
  float value;
  float highRange;
  float lowRange;
  float highLimit;//for alarm high
  float lowLimit;//for alarm low
  float increment;
  boolean highAlarm = false;
  boolean lowAlarm = false;
}parameter;

typedef struct dataMenu{
  int id;//
  boolean hasParameter;//is a Parameter
  String pesan1;//pesan untuk baris pertama (1)
  String pesan2;//pesan untuk baris kedua (2)
}dataMenu;

class AccessDataMenu{
  public:
    static unsigned char menuNbr;
    static unsigned char getmenuNbr(){
      return menuNbr;
    }
    AccessDataMenu(String );
    void add(dataMenu);
    dataMenu read(int);
  private:
    dataMenu  _dataMenu[MAX_MENU];
    String    _id;
};//end of class

class AccessParameter{
  public:
    static unsigned char paramNbr;
    static unsigned char getParamNbr(){
      return paramNbr;
    }
    AccessParameter(String );
    String toString(parameter);
    void add(parameter);
    parameter increaseParameter(parameter,int);
    parameter decreaseParameter(parameter,int);
    void setParameter(int,parameter);
    parameter getParameter(int);
    int getIndexParameter(parameter);
    int getIndexMenu(int);
  private:
    parameter  _parameter[MAX_MENU-1];
    String    _id;
    void _checkAlarm(parameter);
};//end of class

#endif
