#ifndef param_h
#define param_h

    const int NO_ALARM = 0;
    const int HIGH_ALARM = 1;
    const int LOW_ALARM = 2;

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