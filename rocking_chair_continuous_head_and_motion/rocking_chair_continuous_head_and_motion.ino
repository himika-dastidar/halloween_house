#include <Servo.h>

Servo headServo;  // create Servo object to control a servo
Servo rockingChairServo;

int pos = 0;    // variable to store the servo position
int rockingServoPin = 4;
int pirPin = 7;
int headServoPin = 9;

int counter = 0;
int ZERO = 0;
int SERVO_ROTATION_DELAY = 15;
int COORD_DELAY = 500;
bool isRocking = true;
bool motionDetected = false;

unsigned long currentMillis = 0;
unsigned long lastChairRock = 0;

void setup() {
  pinMode(pirPin, INPUT);    // sets PIR pin as the input
  headServo.attach(headServoPin);  // attaches the servo on pin 9 to the Servo object
  rockingChairServo.attach(rockingServoPin);
  headServo.write(ZERO);
  rockingChairServo.write(ZERO);
  Serial.begin(9600);
}

void rockChair() {
    for (pos = ZERO; pos <= 180; pos += 5) {
      // in steps of 1 degree
      rockingChairServo.write(pos);               
      delay(SERVO_ROTATION_DELAY);                        
    }

    for (pos = 180; pos >= 0; pos -= 5) {
      rockingChairServo.write(pos);              
      delay(SERVO_ROTATION_DELAY);
    }
    delay(500);
}

void moveHead() {
  if (motionDetected) {
    // delay before the head turns
    Serial.print("Motion detected");
    Serial.println(counter++);

    // Turns head left
    for (pos = ZERO; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      headServo.write(pos);              
      delay(SERVO_ROTATION_DELAY);
    }

    // Turn head back
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      headServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(SERVO_ROTATION_DELAY);                       // waits 15 ms for the servo to reach the position
    }
  } else {
    Serial.println("Motion not detected");
    headServo.write(ZERO);
  }
}

bool pollMotionDetected() {
  motionDetected = digitalRead(pirPin) == HIGH || motionDetected;
}

void moveRockingChairServo(int start, int end) {
    int delta = 0;
    if (start > end) {
      delta = -5;
    } else {
      delta = 5;
    }
    pos = start;
    while(pos != end) {
      rockingChairServo.write(pos);               
      delay(SERVO_ROTATION_DELAY);
      pos += delta;
    }
}
void rockChair2() {

    // do this every 2000 millis
    if (currentMillis > lastChairRock + 5000) {
      moveRockingChairServo(0, 180);
      moveRockingChairServo(180, 0);

      lastChairRock = currentMillis;
    }
}



void loop() {
  // motionDetected = false;

  // pollMotionDetected();
  // rockChair();
  // pollMotionDetected();
  // moveHead();

  currentMillis = millis();
  rockChair2();

}
