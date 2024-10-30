#include <Servo.h>

Servo myservo;  // create Servo object to control a servo
Servo rockingServo;
// twelve Servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int pirPin = 13;
int servoPin = 4;
int rockingChairPin = 3;
int motionDetected = LOW;

void setup() {
  pinMode(pirPin, INPUT);    // sets PIR pin as the input
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the Servo object
  myservo.write(0);
  rockingServo.attach(rockingChairPin);
}

void loop() {
  motionDetected = digitalRead(pirPin);
  if (motionDetected == HIGH) {
    rockingServo.write(180);
    delay(1000);
    myservo.write(180);
    delay(3000);
    myservo.write(0);
  } else {
    myservo.write(0);
  }
}


