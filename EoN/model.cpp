#include    "model.h"

//AccessDataMenu - Class
AccessDataMenu::AccessDataMenu(String id):_id(id){}

void AccessDataMenu::add(dataMenu data){
  this->_dataMenu[menuNbr] = data;
  menuNbr++;
}

dataMenu AccessDataMenu::read(int index){
  return _dataMenu[index];
}

//AccessParam - Class
AccessParam::AccessParam(String id):_id(id){}

void AccessParam::init(String id, param dtParam){
  _id = id;
  _paramJson["id"] = _id;
  _paramJson["unit"] = dtParam.unit;
  _paramJson["value"] = dtParam.value;
  _paramJson["highRange"] = dtParam.highRange;
  _paramJson["lowRange"] = dtParam.lowRange;
  _paramJson["highLimit"] = dtParam.highLimit;
  _paramJson["lowLimit"] = dtParam.lowLimit;
  _paramJson["alfaEma"] = dtParam.alfaEma;
  _paramJson["increment"] = dtParam.increment;

  _param = dtParam;
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

void AccessParam::_checkAlarm(){
  //Alarm Low evaluation
  _param.alarm = NO_ALARM;
  if (_param.value <= _param.lowLimit) {
    _param.alarm = LOW_ALARM;
    return;
  }

  //Alarm High evaluation
  else if (_param.value >= _param.highLimit) {
    _param.alarm = HIGH_ALARM;
    return;
  }
}

void AccessParam::increaseParameter(int idParam){
  float percentInc = ((_param.increment)/100);
  float range = (_param.highRange - _param.lowRange);
  float increment = percentInc * range;
  float tempVal;

  switch (idParam)
  {
    case PARAMETER_LOW_RANGE:
      tempVal = _param.lowRange + increment;
      if(tempVal < _param.lowLimit) _param.lowRange = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_HIGH_RANGE:
      tempVal = _param.highRange + increment;
      if(tempVal < _param.highRange) _param.highRange = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_LOW_LIMIT:
      tempVal = _param.lowLimit + increment;
      if(tempVal < _param.highLimit) _param.lowLimit = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_HIGH_LIMIT:
      tempVal = _param.highLimit + increment;
      if(tempVal < _param.highRange) _param.highLimit = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_INCREMENT:
      _param.increment = _param.increment + _param.increment * DELTA_INCREMENT;
      break;
    
    default:
      break;
  }
}

void AccessParam::decreaseParameter(int idParam){
  float percentInc = ((_param.increment)/100);
  float range = (_param.highRange - _param.lowRange);
  float increment = percentInc * range;
  float tempVal;

  switch (idParam)
  {
    case PARAMETER_LOW_RANGE:
      tempVal = _param.lowRange - increment;
      if(tempVal > _param.lowRange) _param.lowRange = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_HIGH_RANGE:
      tempVal = _param.highRange - increment;
      if(tempVal > _param.highLimit) _param.highRange = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_LOW_LIMIT:
      tempVal = _param.lowLimit - increment;
      if(tempVal > _param.lowLimit) _param.lowLimit = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_HIGH_LIMIT:
      tempVal = _param.highLimit - increment;
      if(tempVal > _param.lowLimit) _param.highLimit = tempVal;
      this->_checkAlarm();
      break;
    
    case PARAMETER_INCREMENT:
      _param.increment = _param.increment - _param.increment * DELTA_INCREMENT;
      break;
    
    default:
      break;
  }
}
