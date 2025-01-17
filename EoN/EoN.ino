
#include    "commSer.h"
#include    <ESP8266WiFi.h>
#include    "uMQTTBroker.h"
#include    "mqttBroker.h"

//global variables

boolean isWfpsValueUpdate = false;
boolean isWfpsParamUpdate = false;

/*
 * Your WiFi config here
 */
// Replace with your network credentials
const char* ssid = "SLAMET_MNTC 4119";
const char* password = "sampon170466";

const unsigned long BLINK_TIME = 1000;

bool WiFiAP = false;      // Do yo want the ESP as AP?

const char* WFPS_VALUE = "WFPS/Value";
const char* WFPS_PARAM = "WFPS/Param";

MqttBroker mqttBroker("Broker");

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial      softSerial(PIN_RX, PIN_TX); // RX, TX

DigitalOutput       lifeLed(LED_BUILTIN);//Pin 2 for Wemos D1
AccessParam         accessParameter("Parameter");//part of MVC pattern

//Variables declaration for CommSer
CommSer         commSer("EoN-Serial");

//for ESP environment, function should be declare first, 
//if not ERRORR !!!!! 
void startWiFiClient();
void startWiFiAP();
void exceptionAct(int);

void setup() {

    Serial.begin(115200);
    delay(500);

    //initialization LEDs
    lifeLed.init(FORWARD_TYPE,"lifeLed");

    //attachment all peripherals for commSer
    commSer.attachModelParameter(&accessParameter);
    commSer.attachSoftwareSerial(&softSerial);

    // Start WiFi
    if (WiFiAP)
    startWiFiAP();
    else
    startWiFiClient();

    // Start the broker
    Serial.println("Starting MQTT broker");
    mqttBroker.init();

    /*
    * Subscribe to anything
    */
    mqttBroker.subscribe(WFPS_PARAM);

    commSer.info();
}

// the loop function runs over and over again forever
void loop() {
    int counter;

    lifeLed.blink(500);//in milli second

    commSer.execute();

    //update value
    if(isWfpsValueUpdate){
        mqttBroker.publish(WFPS_VALUE, (String)counter++);
    }

    //Update parameter
    if(isWfpsParamUpdate){
        mqttBroker.publish(WFPS_PARAM, (String)counter++);
    }
}

//Functions
/*
 * WiFi init stuff
 */
void startWiFiClient()
{
  Serial.println("Connecting to "+(String)ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void startWiFiAP()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
}

void exceptionAct(int exp){
  switch (exp)  {
    case LOCAL_OPERATION_EXCEPTION:
      break;
    
    case LOCAL_PARAMETER_EXCEPTION:
      break;

    case REMOTE_OPERATION_EXCEPTION:
      break;
    
    case REMOTE_PARAMETER_EXCEPTION:
      break;

    default:
      break;
  }
}
