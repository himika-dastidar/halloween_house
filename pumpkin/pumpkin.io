#include <Servo.h>

Servo leftWing;
Servo rightWing;
Servo leftEye;
Servo rightEye;

int pos = 0;    // variable to store the servo position

void setup() {
  leftEye.attach(2);
  rightEye.attach(3);

  rightWing.attach(8);
  leftWing.attach(9);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    leftWing.write(pos);              // tell servo to go to position in variable 'pos'
    rightWing.write(pos);
    leftEye.write(pos);
    rightEye.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    leftWing.write(pos);              // tell servo to go to position in variable 'pos'
    rightWing.write(pos);
    leftEye.write(pos);
    rightEye.write(pos);
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
