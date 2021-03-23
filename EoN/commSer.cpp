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
 
void CommSer::attachSoftwareSerial(SoftwareSerial *softSerial){
    Serial.println("CommSer::attachSoftwareSerial(SoftwareSerial *softSerial)");
    _linkSerial = softSerial;
  }
 
void CommSer::sendValue(JsonObject valueJson){
  // Send the JSON document over the "link" serial port
  serializeJson(valueJson, *_linkSerial);

}

void CommSer::sendParameter(JsonObject paramJson){
    //JsonObject.as<JsonObject>()  paramJson = _accessParameter->getJson();
  serializeJson(paramJson, *_linkSerial);

}

JsonObject CommSer::getParameter(){

  if (_linkSerial->available()) 
    {
      // Allocate the JSON document
      // This one must be bigger than for the sender because it must store the strings
      StaticJsonDocument<192> paramJson;

      // Read the JSON document from the "link" serial port
      DeserializationError err = deserializeJson(paramJson, *_linkSerial);

      if (err == DeserializationError::Ok) 
        {
          // Print the values
          // (we must use as<T>() to resolve the ambiguity)
          // Get a reference to the root object
          JsonObject obj = paramJson.as<JsonObject>();

          // Loop through all the key-value pairs in obj
          Serial.println("\nKey - Value Pair");
          String str;
          for (JsonPair p : obj) {
            str = p.key().c_str();
            str = String (str + " : ");
            str = String (str + p.value().as<String>());
            Serial.println(str);
          }    
        return obj;
        } 
      else 
        {
          // Print error to the "debug" serial port
          Serial.print("deserializeJson() returned ");
          Serial.println(err.c_str());
      
          // Flush all bytes in the "link" serial port buffer
          while (_linkSerial->available() > 0)
            _linkSerial->read();
        }
    }
}

void CommSer::execute(){

  this->getParameter();
    
}
