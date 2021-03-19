#include    "model.h"

AccessMenuJson::AccessMenuJson(String id):_id(id){}

void AccessMenuJson::add(JsonObject doc){
    JsonObject _doc = _menuJson.createNestedObject();
    _doc = doc;
}

JsonObject AccessMenuJson::read(int idx){
    JsonObject _doc;
    return _doc;
}

void AccessMenuJson::info(){
    Serial.println(_id);

    for (JsonObject elem : _menuJson.as<JsonArray>()) {
        
    }
}