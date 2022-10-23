
#include "qt_lib/playable.h"
#include "unocommunicator.h"

Playable<UNO_TEMPALTE_PARAM> playable;
UnoCommunicator unoCommunicator{true};
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  playable.setCommunicator(&unoCommunicator);
  playable.currentScopeMode = MODE_NOTSTARTED;
}

// the loop function runs over and over again forever
void loop() {
  playable.executeCycle();
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(300);           
  // Serial.print("NL\n");            // wait for a second
  // unoMessage.verbose("testVerbose");
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(300);                  // wait for a second
  // count++;
  // if(count==3){unoMessage.critical("DONE");}
}
