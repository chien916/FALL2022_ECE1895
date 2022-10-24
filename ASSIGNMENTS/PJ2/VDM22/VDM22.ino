
#include "qt_lib/playable.h"
#include "unocommunicator.h"
int s = 0;
Playable<UNO_TEMPALTE_PARAM> playable;
UnoCommunicator unoCommunicator(false);
void setup() {
  playable.setCommunicator(&unoCommunicator);
  playable.currentScopeMode = MODE_NOTSTARTED;
}

// the loop function runs over and over again forever
void loop() {
  // unoCommunicator.buildVerboseMessage("loop\n");
  playable.executeCycle();
}
