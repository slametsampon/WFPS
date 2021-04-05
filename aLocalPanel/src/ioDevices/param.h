#include "Arduino.h"
#include  <ArduinoJson.h>
#include "signalConst.h"

#ifndef param_h
#define param_h

    const int PARAMETER_VALUE = 0;
    const int PARAMETER_LOW_RANGE = 1;
    const int PARAMETER_HIGH_RANGE = 2;
    const int PARAMETER_LOW_LIMIT = 3;
    const int PARAMETER_HIGH_LIMIT = 4;
    const int PARAMETER_INCREMENT = 5;
    const float DELTA_INCREMENT = 0.1;

    typedef struct param{
        String unit;//unit
        float value;
        float highRange;
        float lowRange;
        float highLimit;//for alarm high
        float lowLimit;//for alarm low
        float alfaEma;//alfa for EMA Filter (0 - 100) in percentage
        float increment;
        int alarm;
        int operationMode;
    }param;

    class AccessParam{
    
    public:
        AccessParam(String);
        void init(String, param);
        JsonObject getJson();
        JsonObject getOperation();
        param getParam();
        void setParam(param);
        void setValue(float);
        void setAlarm(int);
        void setOperationMode(int);
        String toString();
        void info();

    private:
        String    _id;
        param _param;

    };//end of class
#endif