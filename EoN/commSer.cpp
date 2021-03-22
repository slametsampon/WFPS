/*
  commSer.h - Library untuk commSer
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021
*/

#include    "commSer.h"

CommSer::CommSer(String id):_id(id){}

void CommSer::info(){
    Serial.println(_id);
}

void CommSer::attachModelParameter(AccessParam *accessParameter){
    Serial.println("CommSer::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
 

void CommSer::sendValue(JsonObject valueJson){

}

void CommSer::sendParameter(JsonObject paramJson){
    //JsonObject.as<JsonObject>()  paramJson = _accessParameter->getJson();

}

JsonObject CommSer::getParameter(){
    JsonObject  paramJson;

    return paramJson;
}

void CommSer::execute(){
    
}
