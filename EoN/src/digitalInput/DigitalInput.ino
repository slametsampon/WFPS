/*
    It is just for testing only, for switchExt usage
    
*/

#include "digitalInput.h"

const char PB_GREEN = 2;


DigitalInput pbGreen(PB_GREEN);//use pin PB_GREEN for P/B

void setup() {

    Serial.begin(115200);

    //initialization switch
    pbGreen.init();
    Serial.println(pbGreen.info());
}

// the loop function runs over and over again forever
void loop() {
}
