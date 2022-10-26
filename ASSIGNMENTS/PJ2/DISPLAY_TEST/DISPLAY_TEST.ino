#include "unocommunicator.h"


UnoCommunicator* unoCommunicatorPtr{ nullptr };
void setup() {
  // Serial.begin(9600);
  // Serial.write('A');
  // Serial.begin(115200);
  unoCommunicatorPtr = new UnoCommunicator(false);
  // unoCommunicatorPtr->platformSpecificFlashPixelToScreen(5,0);
}

// the loop function runs over and over again forever
void loop() {
  // unoCommunicatorPtr->platformSpecificFlashPixelToScreen(0,0);
  // unoCommunicatorPtr->platformSpecificFlashPixelToScreen(0,0);
  // unoCommunicatorPtr->platformSpecificFlashPixelToScreen(5,0);
  // Serial.println("testNormal");
  // // unoCommunicatorPtr->buildVerboseMessage("testBuildVerbsoe");

    unoCommunicatorPtr->platformSpecificFlashPixelToScreen(100,0);
  unoCommunicatorPtr->platformSpecificFlashPixelToScreen(0,0);
  // for(size_t ind=0; ind < 15; ++ind) 
  // unoCommunicatorPtr->platformSpecificFlashPixelToScreen(verticalLine[ind][0], verticalLine[ind][1]);
  // unoCommunicatorPtr->unoDigitalWrite(15,15);
}