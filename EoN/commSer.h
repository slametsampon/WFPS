/*
  commSer.h - Library untuk commSer
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam March 22, 2021
*/
#ifndef commSer_h
#define commSer_h

#include    "Arduino.h"
#include    <ArduinoJson.h>
#include    "Model.h"

class CommSer
{
  public:

    CommSer(String);//constructor
    void info();
    void sendValue(JsonObject);
    void sendParameter(JsonObject);
    JsonObject getParameter();
    void attachModelParameter(AccessParam*);//Pasang Model parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void execute();

  private:

    String _id;
    AccessParam *_accessParameter;
};//end of class

#endif