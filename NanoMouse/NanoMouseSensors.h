#include <Arduino.h>
//#include "CommonUtils.h"

template <byte frontDetector, byte leftDetector, byte rightDetector>

class NanoMouseSensors {
  public:
    void view() {
      //DPRINTLN("IR Sensors...");
      DPRINT("Front: ");
      //Serial.print(analogRead(frontDetector));
      DPRINTLN(analogRead(frontDetector));
      //DPRINT("Left: ");
      //DPRINTLN(analogRead(leftDetector));
      //DPRINT("Right: ");
      //DPRINTLN(analogRead(rightDetector));
    }
};

