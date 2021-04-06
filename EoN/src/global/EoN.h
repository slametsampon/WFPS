/*
All constants for local panel
*/

#ifndef EoN_h
#define EoN_h

    //Wemos R1
    const int PIN_RX    = 5; //D1
    const int PIN_TX    = 4; //D2

    //Operation mode
    const int MODE_READY = 0;
    const int MODE_AUTO = 1;
    const int MODE_AUTO_ON = 2;
    const int MODE_MANUAL = 3;
    const int MODE_MANUAL_ON = 4;
    const int MODE_RESET = 5;
    const int MODE_TEST = 99;

    //Exception code
    const int NO_EXCEPTION = 0;
    const int OPERATION_EXCEPTION = 1;//change on value or operation mode
    const int PARAMETER_EXCEPTION = 2;//change on parameter
    const int REMOTE_OPERATION_EXCEPTION = 3;//change on value or operation mode remotely
    const int REMOTE_PARAMETER_EXCEPTION = 4;//change on parameter remotely

    const int ADC_MAX = 1023;//10 bits
    const int ALFA_EMA = 80;//AlfaEma filter
    const int DEBOUNCING_TIME = 500;//milli second

    const int BLINK_NORMAL = 500;//milli second
    const int BLINK_WARNING = 250;//milli second
    const int BLINK_ERROR = 125;//milli second

#endif
