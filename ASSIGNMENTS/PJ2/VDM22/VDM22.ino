
#include "unocommunicator.h"
#include "qt_lib/gameimpl/gameplay.h"

UnoCommunicator unoCommunicator;
GamePlay gamePlay(
  dynamic_cast<Communicator<8>*>(&unoCommunicator),
  dynamic_cast<Message*>(&unoMessage));
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.print(int(sizeof((unsigned char)(4))));
}

// the loop function runs over and over again forever
void loop() {
  UnoCommunicator unoCommunicator;
  UnoMessage unoMessage;
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(300);           
  // Serial.print("NL\n");            // wait for a second
  // unoMessage.verbose("testVerbose");
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(300);                  // wait for a second
  // count++;
  // if(count==3){unoMessage.critical("DONE");}
}
