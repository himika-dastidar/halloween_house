#include <Servo.h>

// Ping sensor
const int pingPin = 7;
long pingSendTime = 0;

const int MAX_POS = 90;
Servo myservo;   // create servo object to control a servo
Servo myservo2;  // create second servo object

int pos = 0;     // variable to store the position of the first servo
int pos2 = 0;    // variable to store the position of the second servo

void setup() {
  myservo.attach(9);         // attaches the first servo on pin 9
  myservo2.attach(10);       // attaches the second servo on pin 10
  randomSeed(analogRead(A0)); // Initialize random seed
}

void loop() {
  // Ping sensor code:
  if (millis() > pingSendTime + 100) {
    long duration;
    pingSendTime = millis();
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    // The same pin is used to read the signal from the PING sensor
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);

    int choice = random(0, 2);; // Randomly picks either 0 or 1


    // spider
    if (choice == 1) { // Trick case
      if (duration < 380 && duration > 100) {
        for (pos = 0; pos <= MAX_POS; pos += 1) {
          myservo.write(pos); // tell servo to go to position in variable 'pos'
          delay(1);
        }
        delay(1000);
        for (pos = MAX_POS; pos >= 0; pos -= 1) {
          myservo.write(pos);
          delay(15);
        }
      }
    }

    // candy
    if (choice == 0) { // Treat case
      if (duration < 380 && duration > 100) {
        for (pos2 = 0; pos2 <= MAX_POS; pos2 += 1) {
          myservo2.write(pos2); // tell servo to go to position in variable 'pos2'
          delay(1);
        }
        delay(1000);
        for (pos2 = MAX_POS; pos2 >= 0; pos2 -= 1) {
          myservo2.write(pos2);
          delay(15);
        }
      }
    }
  }
  // End ping sensor code
} // void loop
