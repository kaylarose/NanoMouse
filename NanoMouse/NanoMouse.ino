#include <Servo.h>
#include "CommonUtils.h"
#include "NanoMouseMotors.h"
#include "NanoMouseSensors.h"

const byte  LEFT_SERVO_PIN = 6;
const byte  RIGHT_SERVO_PIN = 5;
const byte  BUTTON_PIN = 9;

NanoMouseMotors motors;
NanoMouseSensors<A6, A7, A5> sensors;
CommonUtils utils;

void setup() {
  // TODO move to debug utils
  Serial.begin(9600);

  motors.attach(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

  // Uncomment for enabling Blink Test Mode.
  pinMode(LED_BUILTIN, OUTPUT);

  // Enables movement (must rewatch video)
  // Starts the Robot
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  while (digitalRead(BUTTON_PIN)) {
    // no-op
  }
}

void loop() {
  //   utils.blinkTest();
  //   motors.square();
  //   motors.move(500, 500);
  //   motors.delay(1000);
  //   motors.move(0, 500);
  //   motors.delay(1700);
  //motors.spiral();
   sensors.view();
   delay(100);
}
