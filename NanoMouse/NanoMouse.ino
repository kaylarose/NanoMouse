#include <Servo.h>

#define LEFT_DIRECTION -1
#define RIGHT_DIRECTION 1
#define DEBUG 1

#ifdef DEBUG
  #define DPRINT(...)    Serial.print(__VA_ARGS__);
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__);
#else
  #define DPRINT(...)
  #define DPRINTLN(...)
#endif

Servo leftServo;
Servo rightServo;

const byte  LEFT_SERVO_PIN = 6;
const byte  RIGHT_SERVO_PIN = 5;
const byte  SERVO_POWER_LEVEL = 250; // 200 is max
// The Breadboard Button
const byte  BUTTON_PIN = 9;

void setup() {
  Serial.begin(9600);  
  // Setup Code for Servos. Tells programs which pins the motors are attached to.
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);

  // Sends "Stop" Pulse in 1500 Microseconds
  // Used for calibration. May need to rerun.
  //  leftServo.writeMicroseconds(1500);
  //  rightServo.writeMicroseconds(1500);

  // Uncomment for enabling Blink Test Mode.
   pinMode(LED_BUILTIN, OUTPUT);

  // Enables movement (must rewatch video)
  // Starts the Robot
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  while(digitalRead(BUTTON_PIN)) {
  
  }

  //forwardTime(5000 );
  //delay(1000);
  //stop();
//  turn(LEFT_DIRECTION, 500);
//  turn(RIGHT_DIRECTION, 500);
//   square();
//   //stop(200);
  //  square();
  //   blinkTest();
}


//void stop(int time= 200) {
//  DPRINTLN("Stopping...");
//  // Sends "Stop" Pulse in 1500 Microseconds
//  leftServo.writeMicroseconds(1500);
//  rightServo.writeMicroseconds(1500);
//  delay(time);
//  DPRINTLN("Stopped with time...");
//}


void stop() {
DPRINTLN("Stopping...");
// Sends "Stop" Pulse in 1500 Microseconds
leftServo.writeMicroseconds(1500);
rightServo.writeMicroseconds(1500);
DPRINTLN("Stopped with time...");
}


void forward() {
  DPRINTLN("Moving Forward...");
  leftServo.writeMicroseconds(1500-SERVO_POWER_LEVEL);
  // Inverse power because the servo motor is a different orientation
  // Protip: seems to only apply to parallax motors. Kit motors are pre-calibrated
    // Max 1500...otherwise is reverse......????
  // unsigned int would Go up to max 65k secs (0k/+~65k)
  // signed int would Go up to max 32 (32 bit int) seconds (-32k/+32k)
  // https://www.youtube.com/watch?v=dke4o7A2Y44&feature=youtu.be
  rightServo.writeMicroseconds(1500+SERVO_POWER_LEVEL);
  // TODO This sounds wrong Kayla but it's working that way. Double check.
  // rightServo.writeMicroseconds(1500+SERVO_POWER_LEVEL);
  DPRINTLN("Moved Forward...");
}

void forwardTime(unsigned int time) {  
  DPRINTLN("Moving Forward with time...");
  forward();
  delay(time);
  stop();
  DPRINTLN("Moved Forward with time...");
}


void turn(int direction, int degrees) {
  DPRINTLN("Turning..."+degrees);
  // Because we are using an normal int here, the value is max 32 sec (-32k/+32k), 
  // so if we give multiplier directional args (-1/1) the bot should know hich way to turn.
  leftServo.writeMicroseconds(1500+SERVO_POWER_LEVEL*direction);
  rightServo.writeMicroseconds(1500+SERVO_POWER_LEVEL*direction);
  // TODO Kayla: Refactor this bot https://www.youtube.com/watch?v=5R59dDwAeco
  delay(degrees*5);
  stop();
  DPRINTLN("Turned..."+degrees);
}

void square() {
  DPRINTLN("Starting Square...");
  //forward();
  forwardTime(1500);
  delay(1500);
  //stop(1000);
//  DPRINTLN("L1 Square...");
   turn(LEFT_DIRECTION, 425);
   //delay(1000);
//  //forward();
   forwardTime(1500);
     delay(1500);

//  //stop(1000);
   DPRINTLN("L2 Square...");
   turn(LEFT_DIRECTION, 425);
//  //stop(1000);
//  //forward();
    forwardTime(1500);
    delay(1500);
//  //stop(1000);
  DPRINTLN("L3 Square...");
    turn(LEFT_DIRECTION, 425);
//  //stop(1000);
//  //forward();  
//    forwardTime(1500);
//    delay(1500);
//
//  //stop(1000);
  //forwardTime(1000);
  DPRINTLN("Completed Square...");
}


void blinkTest() {
  DPRINTLN("Blink Board...");
  // Test Code to Validate Board is Responding (Will Blink LED)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void loop() {
  //forward();
  // Uncomment for enabling Blink Test Mode.
  // blinkTest();
   square();
   //forwardTime(1500);
   //forward();
}
