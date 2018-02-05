#include <Servo.h>
#include "CommonUtils.h"
#include "NanoMouseMotors.h"
#include "NanoMouseSensors.h"

////
// PINS
////
const byte LEFT_SERVO_PIN = 6;
const byte RIGHT_SERVO_PIN = 5;
const byte BUTTON_PIN = 9;


CommonUtils utils;
NanoMouseMotors motors;
NanoMouseSensors sensors(A6, 3, A7, 4, A5, 2);

/////
// Program Control via Switch
/////
int switchState;
// Current state of Program 
// LOW == Waiting (default), HIGH == Running
int currentState = LOW;
// Previous state of Program 
// LOW == Waiting (default), HIGH == Running
int previousState = LOW;
// Boolean state of Program 
// false == Waiting (default), true == Running
boolean isRunning = false;
// the last time the Program state was toggled
unsigned long lastToggleTime = 0;
// the debounce (delay) time, to wait in between detecting program state toggle
// (increase if LED output flickers)
const unsigned long DEBOUNCE_DELAY_TIME = 100;


void setup() {
  // TODO move to debug utils
  Serial.begin(9600);

  //motors.attach(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

  sensors.configure();
  
  // Uncomment for enabling Blink Test Mode.
  pinMode(LED_BUILTIN, OUTPUT);

  // Enables movement (must rewatch video)
  // Starts the Robot
  pinMode(BUTTON_PIN, INPUT_PULLUP);

//  while (digitalRead(BUTTON_PIN)) {
//   // no-op
//  }
}

void loop() {
  // Read in the actual switch state
  switchState = digitalRead(BUTTON_PIN);
  
  // Compare the Current and Previous PROGRAM states to the actual SWITCH (Button) State,
  // BUT.... wait a certain ammount of time in between toggling the switch, because
  // the board will register it as multiple button presses, sometimes.
  // TODO, play with this debounce delay. We may not need it because of the delay at the end of the loop.
  if (switchState == HIGH && previousState == LOW && millis() - lastToggleTime > DEBOUNCE_DELAY_TIME) {
    // Toggle Current State
    if (currentState == HIGH) {
      currentState = LOW;
      isRunning = false;
      DPRINTLN("End Program...");
      
      // Do any other "teardown" type stuff when the button is toggled OFF here.
      
    } else {
      currentState = HIGH;
      isRunning = true;
      DPRINTLN("Begin Program...");

      // Do any other "setup" type stuff when the button is toggled ON here.
    }

    // Record the last time we toggled the switch
    lastToggleTime = millis();
  } 

  if (currentState == HIGH) {
    // Program Running...
    sensors.view();
    // delay(100);
  } else {
    // Waiting for program to start...
    // No-Op (uncomment line below to debug)
    // DPRINTLN(".");
    // delay(100);
  }
  previousState = switchState;
  
  // Control the LED Built into the board based on Program state:
  // ON == Running..
  // OFF == Waiting..
  digitalWrite(LED_BUILTIN, currentState);

  delay(100);
}

