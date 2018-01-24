#include <Servo.h>

Servo leftServo;
Servo rightServo;

const byte  LEFT_SERVO_PIN = 6;
const byte  RIGHT_SERVO_PIN = 5;

void setup() {
  // Setup Code for Servos. Tells programs which pins the motors are attached to.
  // Left Servo: Pin 10?!
  // Right Servo: Pin 11?!
//  leftServo.attach(LEFT_SERVO_PIN);
//  rightServo.attach(RIGHT_SERVO_PIN);
//
//  // Sends "Stop" Pulse in 1500 Microseconds
//  leftServo.writeMicroseconds(1500);
//  rightServo.writeMicroseconds(1500);

  //  Uncomment for enabling Blink Test Mode.
   //pinMode(LED_BUILTIN, OUTPUT);
}

void blinkTest() {
  // Test Code to Validate Board is Responding (Will Blink LED)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void loop() {
  // Uncomment for enabling Blink Test Mode.
   //blinkTest();
}

