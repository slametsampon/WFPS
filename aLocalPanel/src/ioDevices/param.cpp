#include "param.h"

//AccessParam - Class
AccessParam::AccessParam(String id):_id(id){}

void AccessParam::init(String id, param dtParam){
  _id = id;

  this->setParam(dtParam);
}

JsonObject AccessParam::getJson(){
  /*
  {
    "header":2,
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

  StaticJsonDocument<128> doc;

  doc["header"] = 2;
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
  */

  // Get a reference to the root object
  StaticJsonDocument<128> doc;
  
  doc["header"] = DATA_PARAMETER;
  doc["id"] = _id;
  doc["unit"] = _param.unit;
  doc["value"] = _param.value;
  doc["highRange"] = _param.highRange;
  doc["lowRange"] = _param.lowRange;
  doc["highLimit"] = _param.highLimit;
  doc["lowLimit"] = _param.lowLimit;
  doc["alfaEma"] = _param.alfaEma;
  doc["increment"] = _param.increment;
  doc["alarm"] = _param.alarm;
  doc["operationMode"] = _param.operationMode;

  return doc.as<JsonObject>();
}

void  AccessParam::setParamJson(JsonObject paramJson){

  //_id = paramJson["id"];
  //_param.unit = paramJson["unit"];

  _param.value = paramJson["value"];
  _param.highRange = paramJson["highRange"];
  _param.lowRange = paramJson["lowRange"];
  _param.highLimit = paramJson["highLimit"];
  _param.lowLimit = paramJson["lowLimit"];
  _param.alfaEma = paramJson["alfaEma"];
  _param.increment = paramJson["increment"];
  _param.alarm = paramJson["alarm"];
  _param.operationMode = paramJson["operationMode"];

}

JsonObject AccessParam::getOperation(){
  /*
  {
    "header":2,
    "id":"Smoke-1",
    "unit":"%",
    "value":51.5,
    "operationMode":2,
    "alarm":2
  }

  StaticJsonDocument<96> doc;

  doc["header"] = 2;
  doc["id"] = "Smoke-1";
  doc["unit"] = "%";
  doc["value"] = 51.5;
  doc["operationMode"] = 2;
  doc["alarm"] = 2;

  serializeJson(doc, output);
  */

  StaticJsonDocument<96> doc;
  doc["header"] = DATA_OPERATION;
  doc["id"] = _id;
  doc["unit"] = _param.unit;
  doc["value"] = _param.value;
  doc["operationMode"] = _param.operationMode;
  doc["alarm"] = _param.alarm;

  return doc.as<JsonObject>();
}

void AccessParam::setOperationJson(JsonObject paramJson){

  _param.operationMode=paramJson["operationMode"];

}

param AccessParam::getParam(){
  return _param;
}

void AccessParam::setValue(float val){
  _param.value =  val;
}

void AccessParam::setAlarm(int val){
  _param.alarm =  val;
}

void AccessParam::setOperationMode(int val){
  _param.operationMode =  val;
}

void AccessParam::setParam(param dataParam){

  _param = dataParam;
}

String AccessParam::getId(){
  return _id;
}

String AccessParam::toString(){
  String str = _id;
  String alm = "-N";

  str =  String(str + " ");
  str =  String(str + _param.value);

  str =  String(str + _param.unit);
  
  if (_param.alarm == LOW_ALARM){
    alm = "-L";
  }
  if (_param.alarm == HIGH_ALARM){
    alm = "-H";
  }
  str =  String(str + alm);
  return str;
}

void AccessParam::info(){

  JsonObject paramJson = this->getJson();

  String str;
  for (JsonPair p : paramJson) {
    str = p.key().c_str();
    str = String (str + " : ");
    str = String (str + p.value().as<String>());
    Serial.println(str);
  }    
}
