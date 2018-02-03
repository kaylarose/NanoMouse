#include <Arduino.h>
//#include "CommonUtils.h"

template <byte frontDetector, byte leftDetector, byte rightDetector>

class NanoMouseSensors {
  public: 
    void view() {
      DPRINTLN("IR Sensors...");
      //DPRINTLN("F:");
      //DPRINTLN(analogRead(frontDetector));
      //DPRINTLN("L:");
      //DPRINTLN(analogRead(leftDetector));
      DPRINTLN("R:");
      DPRINTLN(analogRead(rightDetector));
    }
};
