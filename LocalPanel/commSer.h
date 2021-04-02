/*
  commSer.h - Library untuk commSer
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021

? value
StaticJsonDocument<48> doc;

doc["id"] = "Smoke-1";
doc["value"] = 51.5;

serializeJson(doc, output);

? Stream& input;

StaticJsonDocument<48> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

const char* id = doc["id"]; // "Smoke-1"
float value = doc["value"]; // 51.5

? Parameter
{
  "id":"Smoke-1",
  "unit":"%",
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
doc["value"] = 51.5;
doc["highRange"] = 100;
doc["lowRange"] = 0;
doc["highLimit"] = 80;
doc["lowLimit"] = 40;
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
float increment = doc["increment"]; // 1.1

*/

#ifndef commSer_h
#define commSer_h

#include    "Arduino.h"
#include    <ArduinoJson.h>
#include    "src\model\model.h"

class CommSer
{
  public:

    CommSer(String);//constructor
    void info();
    void sendValue(JsonObject);
    void sendParameter(JsonObject);
    JsonObject getParameter();
    void attachModelParameter(AccessParam*);//Pasang Model parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void execute();

  private:

    String _id;
    AccessParam *_accessParameter;
};//end of class

#endif