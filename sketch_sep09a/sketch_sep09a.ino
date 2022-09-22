#include <RedBot.h>  // This line "includes" the library into your sketch.
#include <NewPing.h>
// https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home

RedBotMotors motors; // Instantiate the motor control object.

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping

const int leftPhotoresistor = A2;
const int rightPhotoresistor = A3;
const int rightEcho = A0;
const int leftEcho = A4;
const int rightTrig = A1;
const int leftTrig = A5;

int leftRes;
int rightRes;
int leftDistance;
int rightDistance;
long leftDuration;
long rightDuration;

NewPing sonar[SONAR_NUM] = {
  NewPing sonar(leftTrig, leftEcho, MAX_DISTANCE);
  NewPing sonar(rightTrig, rightEcho, MAX_DISTANCE);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(leftTrig, OUTPUT);
//  pinMode(rightTrig, OUTPUT);
//  pinMode(leftEcho, INPUT);
//  pinMode(rightEcho, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  photoResistorValues();
  echoValues();
  obstacleCollosion();
  delay(500);
}

void forward() {
  // Forward
  motors.rightMotor(-111);
  motors.leftMotor(105);
}

void backwards() {
  motors.rightMotor(111);
  motors.leftMotor(-105);
}

void turnRight() {
  // Turn right when the ass of the bot is facing you
  motors.rightMotor(-220);
  motors.leftMotor(24);
}

void turnLeft() {
  // Turn left when the ass of the bot is facing you
  motors.leftMotor(220);
  motors.rightMotor(-24);
}

void echoValues() {
  digitalWrite(leftTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrig, LOW);
  leftDuration = pulseIn(leftEcho, HIGH);
  leftDistance = leftDuration * 0.034 / 2;

  digitalWrite(rightTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrig, LOW);
  rightDuration = pulseIn(rightEcho, HIGH);
  rightDistance = rightDuration * 0.034 / 2;
  
  Serial.print("Left distance: ");
  Serial.print(leftDistance);
  Serial.println(" cm");
  Serial.print("Right distance: ");
  Serial.print(rightDistance);
  Serial.println(" cm");
}

void photoResistorValues() {
  leftRes = analogRead(leftPhotoresistor);
  rightRes = analogRead(rightPhotoresistor);
  
  Serial.print("Left photoresistor value: ");
  Serial.println(leftRes);
  Serial.print("Right photoresistor value: ");
  Serial.println(rightRes);
}

void obstacleCollosion() {
  if ((rightDistance <= 18) && (leftDistance <= 18)) {
    Serial.println("Moving Backwards ");
    backwards();
  }
  
  else if (rightDistance <= 18) {
    Serial.println("Turning Left ");
    turnLeft();
  }

  else if (leftDistance <= 18) {
    Serial.print("Turning Right ");
    turnRight();
  }

  else {
    Serial.println("Forward");
    forward();
  }
}
