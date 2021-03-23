/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
  JSON

StaticJsonDocument<96> doc;

doc["id"] = "Smoke-1";
doc["unit"] = "%";
doc["value"] = 51.5;
doc["highRange"] = 100;
doc["lowRange"] = 0;
doc["highLimit"] = 80;
doc["lowLimit"] = 40;
doc["alfaEma"] = 75.5;
doc["increment"] = 1.1;

serializeJson(doc, output);

? Stream& input;

StaticJsonDocument<192> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

const char* id = doc["id"]; // "Smoke-1"
const char* unit = doc["unit"]; // "%"
float value = doc["value"]; // 51.5
int highRange = doc["highRange"]; // 100
int lowRange = doc["lowRange"]; // 0
int highLimit = doc["highLimit"]; // 80
int lowLimit = doc["lowLimit"]; // 40
float alfaEma = doc["alfaEma"]; // 75.5
float increment = doc["increment"]; // 1.1
*/
#ifndef model_h
#define model_h

#include "Arduino.h"
#include  <ArduinoJson.h>
#include "src/analogInput/param.h"

const int MAX_MENU = 3;
const int PARAMETER_VALUE = 0;
const int PARAMETER_LOW_RANGE = 1;
const int PARAMETER_HIGH_RANGE = 2;
const int PARAMETER_LOW_LIMIT = 3;
const int PARAMETER_HIGH_LIMIT = 4;
const int PARAMETER_INCREMENT = 5;
const float DELTA_INCREMENT = 0.1;

typedef struct dataMenu{
  boolean isHasParam;//is has a Parameter
  char* Messages_0;//pesan untuk baris pertama (1)
  char* Messages_1;//pesan untuk baris kedua (2)
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

class AccessParam{
  
  public:
    AccessParam(String);
    void init(String, param);
    JsonObject getJson();
    param getParam();
    String toString();
    void updateJson(JsonObject);
    void increaseParameter(int);
    void decreaseParameter(int);
    void info();

  private:
    String    _id;
    StaticJsonDocument<192> _paramJson;
    param _param;

    void _checkAlarm();
};//end of class

#endif
