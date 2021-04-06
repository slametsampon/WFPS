/*
? Pin Function ESP-8266 Pin
? Wemos D1 Mini

TX TXD TXD
RX RXD RXD
A0 Analog in(max 3.3V) A0
D0 IO GPIO16
D1 IO, SCL GPIO5
D2 IO, SDA GPIO4
D3 IO,Pull-up GPIO0
D4 IO,pull-up,LED GPIO2
D5 IO, SCK GPIO14
D6 IO, MISO GPIO12
D7 IO, MOSI GPIO13
D8 IO,pull-down, SS GPIO15
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
    const int LOCAL_OPERATION_EXCEPTION = 1;//change on value or operation mode locally
    const int LOCAL_PARAMETER_EXCEPTION = 2;//change on parameter locally
    const int REMOTE_OPERATION_EXCEPTION = 3;//change on value or operation mode remotely
    const int REMOTE_PARAMETER_EXCEPTION = 4;//change on parameter remotely

    const int ADC_MAX = 1023;//10 bits
    const int ALFA_EMA = 80;//AlfaEma filter
    const int DEBOUNCING_TIME = 500;//milli second

    const int BLINK_NORMAL = 500;//milli second
    const int BLINK_WARNING = 250;//milli second
    const int BLINK_ERROR = 125;//milli second

#endif
