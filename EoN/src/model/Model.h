/*
  Model.h - Library untuk Model
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 15, 2021
  JSON

{
  "id":"ZONE-1",
  "Mode":1,
  "Status":"N"
  }
StaticJsonDocument<48> doc;

doc["id"] = "ZONE-1";
doc["Mode"] = 1;
doc["Status"] = "N";

serializeJson(doc, output);

Parameter[
{
  "id":"ZONE-1",
  "Mode":1,
  "Status":"N"
  },
{
  "id":"ZONE-2",
  "Mode":1,
  "Status":"N"
  },
{
  "id":"ZONE-3",
  "Mode":3,
  "Status":"N"
  },
{
  "id":"ZONE-4",
  "Mode":5,
  "Status":"N"
  },
{
  "id":"ZONE-5",
  "Mode":4,
  "Status":"N"
  },
{
  "id":"ZONE-6",
  "Mode":3,
  "Status":"N"
  },
{
  "id":"ZONE-7",
  "Mode":2,
  "Status":"N"
  },
{
  "id":"ZONE-8",
  "Mode":4,
  "Status":"A"
  }
]
StaticJsonDocument<384> doc;

JsonObject doc_0 = doc.createNestedObject();
doc_0["id"] = "ZONE-1";
doc_0["Mode"] = 1;
doc_0["Status"] = "N";

JsonObject doc_1 = doc.createNestedObject();
doc_1["id"] = "ZONE-2";
doc_1["Mode"] = 1;
doc_1["Status"] = "N";

JsonObject doc_2 = doc.createNestedObject();
doc_2["id"] = "ZONE-3";
doc_2["Mode"] = 3;
doc_2["Status"] = "N";

JsonObject doc_3 = doc.createNestedObject();
doc_3["id"] = "ZONE-4";
doc_3["Mode"] = 5;
doc_3["Status"] = "N";

JsonObject doc_4 = doc.createNestedObject();
doc_4["id"] = "ZONE-5";
doc_4["Mode"] = 4;
doc_4["Status"] = "N";

JsonObject doc_5 = doc.createNestedObject();
doc_5["id"] = "ZONE-6";
doc_5["Mode"] = 3;
doc_5["Status"] = "N";

JsonObject doc_6 = doc.createNestedObject();
doc_6["id"] = "ZONE-7";
doc_6["Mode"] = 2;
doc_6["Status"] = "N";

JsonObject doc_7 = doc.createNestedObject();
doc_7["id"] = "ZONE-8";
doc_7["Mode"] = 4;
doc_7["Status"] = "A";

serializeJson(doc, output);

{
  "id":1,
  "Messages": {"line1":"message11-message12-message13-message14-", "line2":"message21-message22-message23-message24-"}
  }

StaticJsonDocument<128> doc;

doc["id"] = 1;

JsonObject Messages = doc.createNestedObject("Messages");
Messages["line1"] = "message11-message12-message13-message14-";
Messages["line2"] = "message21-message22-message23-message24-";

serializeJson(doc, output);

Menu
{
  "Messages": ["message11-message12-message13-message14-",
              "message21-message22-message23-message24-",
              "message31-message32-message33-message34-",
              "message41-message42-message43-message44-"]
  }

StaticJsonDocument<256> doc;

JsonArray Messages = doc.createNestedArray("Messages");
Messages.add("message11-message12-message13-message14-");
Messages.add("message21-message22-message23-message24-");
Messages.add("message31-message32-message33-message34-");
Messages.add("message41-message42-message43-message44-");

serializeJson(doc, output);

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

JsonArray Messages = doc["Messages"];
const char* Messages_0 = Messages[0]; // "message11-message12-message13-message14-"
const char* Messages_1 = Messages[1]; // "message21-message22-message23-message24-"
const char* Messages_2 = Messages[2]; // "message31-message32-message33-message34-"
const char* Messages_3 = Messages[3]; // "message41-message42-message43-message44-"

*/
#ifndef model_h
#define model_h

#include "Arduino.h"
#include  <ArduinoJson.h>


class AccessMenuJson{
  public:
    AccessMenuJson(String);
    void add(String);
    void insert(int, String);
    String read(int);
    void info();
  private:
    String    _id;
    StaticJsonDocument<256> _menuJson;
    JsonArray _messages = _menuJson.createNestedArray("Messages");
};//end of class

#endif
