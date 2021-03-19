    typedef struct aiParam{
        String unit;//unit
        float value;
        float highRange;
        float lowRange;
        float highLimit;//for alarm high
        float lowLimit;//for alarm low
        unsigned int alfaEma;//alfa for EMA Filter (0 - 100) in percentage
        int alarm;
    }aiParam;
