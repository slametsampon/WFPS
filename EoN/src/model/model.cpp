#include    "model.h"

AccessMenuJson::AccessMenuJson(String id):_id(id){}

void AccessMenuJson::add(String msg){
    _messages.add(msg);
}

void AccessMenuJson::insert(int idx, String msg){
    _messages[idx] = msg;
}

String AccessMenuJson::read(int idx){
    return _messages[idx];
}

void AccessMenuJson::info(){
    Serial.println(_id);
}