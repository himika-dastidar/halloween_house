#include <Servo.h>

Servo headServo;  // create Servo object to control a servo
Servo rockingChairServo;

int pos = 0;    // variable to store the servo position
int rockingServoPin = 4;
int pirPin = 7;
int headServoPin = 9;

int motionDetected = LOW;
int counter = 0;
int ZERO = 0;
int SERVO_ROTATION_DELAY = 15;
int COORD_DELAY = 500;

void setup() {
  pinMode(pirPin, INPUT);    // sets PIR pin as the input
  headServo.attach(headServoPin);  // attaches the servo on pin 9 to the Servo object
  rockingChairServo.attach(rockingServoPin);
  headServo.write(ZERO);
  rockingChairServo.write(ZERO);
  Serial.begin(9600);
}

void loop() {
  motionDetected = digitalRead(pirPin);
  if (motionDetected == HIGH) {
    // delay before the head turns
    delay(COORD_DELAY);
    Serial.print("Motion detected");
    Serial.print(counter++);

    for (pos = ZERO; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      headServo.write(pos);              
      delay(SERVO_ROTATION_DELAY);
    }

    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      headServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(SERVO_ROTATION_DELAY);                       // waits 15 ms for the servo to reach the position
    }

    // delay before the chair starts rocking
    delay(COORD_DELAY);

    for (pos = ZERO; pos <= 180; pos += 5) {
      // in steps of 1 degree
      rockingChairServo.write(pos);               
      delay(SERVO_ROTATION_DELAY);                        
    }

    for (pos = 180; pos >= 0; pos -= 1) {
      rockingChairServo.write(pos);              
      delay(SERVO_ROTATION_DELAY);
    }
  } else {
    Serial.print("Motion not detected");
    headServo.write(ZERO);
    rockingChairServo.write(ZERO);
  }
}
