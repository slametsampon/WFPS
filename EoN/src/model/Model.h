/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
  JSON

menu
[
  {
    "isParam": false,
    "Messages": [
      "message11-message12-message13-message14-",
      "message21-message22-message23-message24-"
    ]
  },
  {
    "isParam": true,
    "Messages": [
      "message31-message32-message33-message34-",
      "message41-message42-message43-message44-"
    ]
  }  
]

StaticJsonDocument<384> doc;

JsonObject doc_0 = doc.createNestedObject();
doc_0["isParam"] = false;

JsonArray doc_0_Messages = doc_0.createNestedArray("Messages");
doc_0_Messages.add("message11-message12-message13-message14-");
doc_0_Messages.add("message21-message22-message23-message24-");

JsonObject doc_1 = doc.createNestedObject();
doc_1["isParam"] = true;

JsonArray doc_1_Messages = doc_1.createNestedArray("Messages");
doc_1_Messages.add("message31-message32-message33-message34-");
doc_1_Messages.add("message41-message42-message43-message44-");

serializeJson(doc, output);

? Stream& input;

StaticJsonDocument<384> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

for (JsonObject elem : doc.as<JsonArray>()) {

  bool isParam = elem["isParam"]; // false, true

  const char* Messages_0 = elem["Messages"][0]; // "message11-message12-message13-message14-", ...
  const char* Messages_1 = elem["Messages"][1]; // "message21-message22-message23-message24-", ...

}

*/
#ifndef model_h
#define model_h

#include "Arduino.h"
#include  <ArduinoJson.h>


class AccessMenuJson{
  public:
    AccessMenuJson(String);
    void add(JsonObject);
    JsonObject read(int);
    void info();
  private:
    String    _id;
    StaticJsonDocument<384> _menuJson;
};//end of class

#endif
