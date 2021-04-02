/*
All constants for local panel
*/

#ifndef localPanelConst_h
#define localPanelConst_h

    #define PIN_KEYPAD A0 // pin Analog Keypad

    const int LCD_RS            = 8;
    const int LCD_EN            = 9;
    const int LCD_D4            = 4;
    const int LCD_D5            = 5;
    const int LCD_D6            = 6;
    const int LCD_D7            = 7;

    const int PIN_PB_AUTO       = 23; 
    const int PIN_PB_MANUAL     = 25; 
    const int PIN_PB_RESET      = 27; 
    const int PIN_PB_TEST       = 29; 

    const int PIN_ADDR0         = 31; 
    const int PIN_ADDR1         = 33; 
    const int PIN_ADDR2         = 35; 


    const int PIN_LED_AUTO      = 22; 
    const int PIN_LED_MANUAL    = 24; 
    const int PIN_LED_RESET     = 26; 

    const int PIN_SOLENOID_VALVE = 28; 

    const int MAX_MENU = 3;
    const int MODE_MENU_MAIN = 1;
    const int MODE_MENU_PARAMETER = 2;
    const int MODE_CHANGE_PARAMETER = 3;

    const int DEFAULT_INDEX = 999;

#endif
