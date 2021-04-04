#include "param.h"

//AccessParam - Class
AccessParam::AccessParam(String id):_id(id){}

void AccessParam::init(String id, param dtParam){
  _id = id;

  this->setParam(dtParam);
}

void AccessParam::updateJson(JsonObject paramJson){
  _paramJson = paramJson;
}

JsonObject AccessParam::getJson(){
  // Get a reference to the root object

  return _paramJson.as<JsonObject>();
}

param AccessParam::getParam(){
  return _param;
}

void AccessParam::setValue(float val){
  _param.value =  val;
  _paramJson["value"] = _param.value;
}

void AccessParam::setAlarm(int val){
  _param.alarm =  val;
  _paramJson["alarm"] = _param.alarm;
}

void AccessParam::setParam(param dataParam){

  _param = dataParam;
  this->_initJson(_param);
}

String AccessParam::toString(){
  String str = _id;
  String alm = "(N)";
  str =  String(str + " ");
  str =  String(str + _param.unit);
  if (_param.alarm == LOW_ALARM){
    alm = "(L)";
  }
  if (_param.alarm == HIGH_ALARM){
    alm = "(H)";
  }
  str =  String(str + alm);
  return str;
}

void AccessParam::info(){
  Serial.println(_id);
  String str;
  for (JsonPair p : _paramJson.as<JsonObject>()) {
    str = p.key().c_str();
    str = String (str + " : ");
    str = String (str + p.value().as<String>());
    Serial.println(str);
  }    
}

void AccessParam::_initJson(param dtParam){

  _paramJson["id"] = _id;
  _paramJson["unit"] = dtParam.unit;
  _paramJson["value"] = dtParam.value;
  _paramJson["highRange"] = dtParam.highRange;
  _paramJson["lowRange"] = dtParam.lowRange;
  _paramJson["highLimit"] = dtParam.highLimit;
  _paramJson["lowLimit"] = dtParam.lowLimit;
  _paramJson["alfaEma"] = dtParam.alfaEma;
  _paramJson["increment"] = dtParam.increment;
  _paramJson["alarm"] = dtParam.alarm;

}