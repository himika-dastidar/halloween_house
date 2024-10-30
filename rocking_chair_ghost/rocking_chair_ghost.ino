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

unsigned long currentMillis = 0;
unsigned long lastChairRock = 0;
unsigned long lastHeadTurn = 0;

void setup() {
  pinMode(pirPin, INPUT);    // sets PIR pin as the input
  headServo.attach(headServoPin);  // attaches the servo on pin 9 to the Servo object
  rockingChairServo.attach(rockingServoPin);
  headServo.write(ZERO);
  rockingChairServo.write(ZERO);
  Serial.begin(9600);
}

unsigned long rockingServoDelay = 0;
bool moveRockingChairServo(int end) {
  if (rockingServoDelay + 10 > currentMillis) {
    return false;
  }
  moveServo(rockingChairServo, end, 2);
  rockingServoDelay = currentMillis;
  int value = rockingChairServo.read();

  // Serial.println(value);
  return value == end;
}

unsigned long headServoDelay = 0;
bool moveHead(int end, int speed) {
  if (headServoDelay + 20 > currentMillis) {
    return false;
  }
  moveServo(headServo, end, speed);
  int value = headServo.read();
  return value == end;
}

void moveServo(Servo& servo, int end, int speed) {
  int delta = 0;
  int pos = servo.read();
  if (pos > end) {
    delta = -1 * speed;
  } else {
    delta = speed;
  }

  servo.write(pos + delta);
}

const int ROCKING_CHAIR_REST = 0;
const int ROCKING_CHAIR_FORWARD = 1;
const int ROCKING_CHAIR_BACK = 2;

int rockingChairState = 0;
void rockChair() {
    // do this every 2000 millis
    if (lastChairRock + 2000 > currentMillis) {
      return;
    }

    switch(rockingChairState) {
      case ROCKING_CHAIR_REST:
        rockingChairState = ROCKING_CHAIR_FORWARD;
        break;
      case ROCKING_CHAIR_FORWARD:
        if (moveRockingChairServo(180)) {
          rockingChairState = ROCKING_CHAIR_BACK;
        }
        break;
      case ROCKING_CHAIR_BACK:
        if (moveRockingChairServo(0)) {
          rockingChairState = ROCKING_CHAIR_REST;
          lastChairRock = currentMillis;
        } 
        break;
    }
}

const int HEAD_TURN_DETECT = 0;
const int HEAD_TURN_LEFT = 1;
const int HEAD_TURN_WAIT = 2;
const int HEAD_TURN_RESET = 3;

int headTurnState = 0;
unsigned long lastHeadWaitTime = 0;

void moveHead() {

  if (lastHeadTurn + 3000 > currentMillis) {
    return;
  }

  switch(headTurnState) {
    case HEAD_TURN_DETECT:
      if (digitalRead(pirPin) == HIGH) {
        // Serial.println("Motion detected");
        headTurnState = HEAD_TURN_LEFT;
      }
      break;
    case HEAD_TURN_LEFT:
      if (moveHead(180, 2)) {
        headTurnState = HEAD_TURN_WAIT;
        lastHeadWaitTime = currentMillis;
      }
      break;
    case HEAD_TURN_WAIT:
      if (currentMillis > (lastHeadWaitTime + 3000)) {
        headTurnState = HEAD_TURN_RESET;
      }
      break;
    case HEAD_TURN_RESET:
      if (moveHead(0, 1)) {
        headTurnState = HEAD_TURN_DETECT;
        lastHeadTurn = currentMillis;
      } 
      break;
  }
}


void loop() {
  currentMillis = millis();
  rockChair();
  moveHead();
}