#include "src\ledExt\ledExt.h"
#include "src\sequenceTimer\sequenceTimer.h"

SequenceTimer SequenceMain("Sequence");
LedExt lifeLed(LED_BUILTIN);

void setup() {
    lifeLed.init();
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    SequenceMain.execute();
    if(SequenceMain.isASecondEvent()){
        //put process every second
    }
    
}
