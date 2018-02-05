#include <Arduino.h>
//#include "CommonUtils.h"

class NanoMouseSensors {
  byte frontDetector;
  byte frontEmitter;
  byte leftDetector;
  byte leftEmitter;
  byte rightDetector;
  byte rightEmitter;
  
  public:
    NanoMouseSensors(byte frontDetectorPin, 
                     byte frontEmitterPin, 
                     byte leftDetectorPin,
                     byte leftEmitterPin,
                     byte rightDetectorPin,
                     byte rightEmitterPin) {

        frontDetector = frontDetectorPin;
        frontEmitter = frontEmitterPin;
        leftDetector = leftDetectorPin;
        leftEmitter = leftEmitterPin;
        rightDetector = rightDetectorPin;
        rightEmitter = rightEmitterPin;
         
    }

    void configure() {
      pinMode(frontEmitter, OUTPUT);
      pinMode(leftEmitter, OUTPUT);
      pinMode(rightEmitter, OUTPUT);

      digitalWrite(frontEmitter, HIGH);
      digitalWrite(leftEmitter, HIGH);
      digitalWrite(rightEmitter, HIGH);
    }
    
    void view() {
      Log::println("L: ", analogRead(leftDetector), "\t",
               "F: ", analogRead(frontDetector), "\t",
               "R: ", analogRead(rightDetector));
    }
};
