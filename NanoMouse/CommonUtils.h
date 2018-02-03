#include <Arduino.h>

#define DEBUG 1

#ifdef DEBUG
  #define DPRINT(...)    Serial.print(__VA_ARGS__);
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__);
#else
  #define DPRINT(...)
  #define DPRINTLN(...)
#endif

class CommonUtils
{
  public:
    void blinkTest() {
      DPRINTLN("Blink Board...");
      // Test Code to Validate Board is Responding (Will Blink LED)
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
};

