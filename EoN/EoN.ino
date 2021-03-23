/*
Pin Function ESP-8266 Pin
Wemos D1 Mini
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

#include    "model.h"
#include    "commSer.h"
#include    "src\digitalOutput\DigitalOutput.h"
#include    <SoftwareSerial.h>


const int PIN_RX    = 5; //D1
const int PIN_TX    = 4; //D2

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial      softSerial(PIN_RX, PIN_TX); // RX, TX

DigitalOutput       lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1
AccessParam         accessParameter("Parameter");//part of MVC pattern

//Variables declaration for CommSer
CommSer         commSer("EoN-Serial");

void setup() {

    Serial.begin(115200);
    delay(500);

    //initialization LEDs
    lifeLed.init("lifeLed");

    //attachment all peripherals for commSer
    commSer.attachModelParameter(&accessParameter);
    commSer.attachSoftwareSerial(&softSerial);

    String str;
    str = String("lifeLed \n");//with new line
    str = String(str + lifeLed.info());
    Serial.println(str);
    
    commSer.info();
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    commSer.execute();
}

