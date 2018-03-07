#include <Servo.h>
#include "CommonUtils.h"
#include "NanoMouseMotors.h"
#include "NanoMouseSensors.h"

////
// PINS
////
const byte LEFT_SERVO_PIN = 8;
const byte RIGHT_SERVO_PIN = 7;
const byte BUTTON_PIN = 6;
const byte LEFT_LED_PIN = 5;
const byte RIGHT_LED_PIN = 9;
const byte FRONT_LED_PIN = 10;

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

  sensors.configure();
  
  // Uncomment for enabling Blink Test Mode.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(FRONT_LED_PIN, OUTPUT);

  // Enables movement (must rewatch video)
  // Starts the Robot
  pinMode(BUTTON_PIN, INPUT_PULLUP);

//  while (digitalRead(BUTTON_PIN)) {
//   // no-op
//  }
}

byte state() {
  byte threshold = 30;
  byte event = 0;
  sensors.sense();

  // 1 = Front
  // 2 = Left
  // 3 = Front and Left
  // 4 = Right
  // 5 = Front and Right
  // 6 = Right and Left
  // 7 = Front, Left, and Right
  if (sensors.front > threshold) {
    event += 1;
  }

  if (sensors.left > threshold) {
    event += 2;
  }

  if (sensors.right > threshold) {
    event += 4;
  }

  return event;
}

void avoid(byte event) {
  digitalWrite(LEFT_LED_PIN, LOW);
  digitalWrite(RIGHT_LED_PIN, LOW);
  digitalWrite(FRONT_LED_PIN, LOW);
  switch(event) {
      case 1:
        Log::println("Turn NOW!! Headed directly into obstacle");
        digitalWrite(LEFT_LED_PIN, HIGH);
        digitalWrite(FRONT_LED_PIN, HIGH);
        motors.turn(LEFT_SERVO_PIN, 90);
        sensors.reinitialize();
        break;
      case 2:
        Log::println("Turn Right.");
        digitalWrite(LEFT_LED_PIN, LOW);
        digitalWrite(RIGHT_LED_PIN, HIGH);
        motors.turn(RIGHT_SERVO_PIN, 45);
        sensors.reinitialize();
        break;
      case 4:
        Log::println("Turn Left.");
        digitalWrite(LEFT_LED_PIN, HIGH);
        digitalWrite(RIGHT_LED_PIN, LOW);
        motors.turn(LEFT_SERVO_PIN, 45);
        sensors.reinitialize();
        break;
      default:
        digitalWrite(LEFT_LED_PIN, LOW);
        digitalWrite(RIGHT_LED_PIN, LOW);
        digitalWrite(FRONT_LED_PIN, HIGH);
        Log::println(".");
        motors.forward();
        sensors.reinitialize();
        break;
  }
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
      motors.stop();
      // Do any other "teardown" type stuff when the button is toggled OFF here.
      
    } else {
      currentState = HIGH;
      isRunning = true;
      DPRINTLN("Begin Program...");
      motors.attach(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

      // Do any other "setup" type stuff when the button is toggled ON here.
    }

    // Record the last time we toggled the switch
    lastToggleTime = millis();
  } 

  if (currentState == HIGH) {
    // Program Running...
    //  while (Serial.available()) {
//    char inChar = (char)Serial.read();
//    switch(inChar) {
//      case '1':
//        digitalWrite(LED_BUILTIN, HIGH);
//      break;
//      case '0':
//        digitalWrite(LED_BUILTIN, LOW);
//      break;
//    }
//    Serial.println(inChar);
//  }

    avoid(state());

    // delay(100);
  } else {
    motors.stop();
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


