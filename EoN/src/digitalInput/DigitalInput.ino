
#include "DigitalInput.h" //Library buatan sendiri

#define   DIG_PIN 2 //Digital Input Pin

DigitalInput inputSwitch(DIG_PIN);

void setup(void) {
  Serial.begin(115200);
  // put your setup code here, to run once:
  inputSwitch.init(REVERSE_DI);
  Serial.println(inputSwitch.info());
}

void loop() {
}
