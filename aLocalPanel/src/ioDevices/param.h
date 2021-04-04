/*
? Parameter
{
  "id":"Smoke-1",
  "unit":"%",
  "value":51.5,
  "highRange":100.0,
  "lowRange":0.0,
  "highLimit":80.0,
  "lowLimit":40.0,
  "increment":1.1,
  "alarm":2
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
doc["alarm"] = 2;

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
int alarm = doc["alarm"]; // 2

*/
#include "Arduino.h"
#include  <ArduinoJson.h>
#include "signalConst.h"

#ifndef param_h
#define param_h

    const int PARAMETER_VALUE = 0;
    const int PARAMETER_LOW_RANGE = 1;
    const int PARAMETER_HIGH_RANGE = 2;
    const int PARAMETER_LOW_LIMIT = 3;
    const int PARAMETER_HIGH_LIMIT = 4;
    const int PARAMETER_INCREMENT = 5;
    const float DELTA_INCREMENT = 0.1;

    typedef struct param{
        String unit;//unit
        float value;
        float highRange;
        float lowRange;
        float highLimit;//for alarm high
        float lowLimit;//for alarm low
        float alfaEma;//alfa for EMA Filter (0 - 100) in percentage
        float increment;
        int alarm;
    }param;

    class AccessParam{
    
    public:
        AccessParam(String);
        void init(String, param);
        JsonObject getJson();
        param getParam();
        void setParam(param);
        void setValue(float);
        void setAlarm(int);
        String toString();
        void updateJson(JsonObject);
        void info();

    private:
        String    _id;
        StaticJsonDocument<192> _paramJson;
        param _param;

        void _initJson(param);

    };//end of class
#endif