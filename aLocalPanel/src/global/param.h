#ifndef param_h
#define param_h

    const int NO_ALARM = 0;
    const int HIGH_ALARM = 1;
    const int LOW_ALARM = 2;

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
    }param;

#endif