#include <RedBot.h>  // This line "includes" the library into your sketch.
#include <NewPing.h>
// https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home

RedBotMotors motors; // Instantiate the motor control object.

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 1000 // Maximum distance (in cm) to ping
#define RIGHTECHO A0
#define RIGHTTRIG A1
#define LEFTPHOTORESISTOR A2
#define RIGHTPHOTORESISTOR A3
#define LEFTECHO A4
#define LEFTTRIG A5

enum
{
  advance,
  left,
  right,
  reverseLeft,
  reverseRight
}machineState;

NewPing sonar[SONAR_NUM] = {
  NewPing(LEFTTRIG, LEFTECHO, MAX_DISTANCE),
  NewPing(RIGHTTRIG, RIGHTECHO, MAX_DISTANCE)
};

float leftRes;
float rightRes;
int ambientLight;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  machineState = advance;
  ambientLight = ((analogRead(LEFTPHOTORESISTOR) + analogRead(RIGHTPHOTORESISTOR)));
}

void loop() {
//  photoResistorValues();
//  Serial.print("ambient light value: ");
//  Serial.println(ambientLight);
//  echoCollision();
  findLight();
//  checkState();
  delay(50);
}

void forward() {
  // Forward
  motors.rightMotor(-111);
  motors.leftMotor(105);
}

void backwardsLeft() {
  motors.rightMotor(24);
  motors.leftMotor(-220);
}

void backwardsRight() {
  motors.rightMotor(-24);
  motors.leftMotor(220);
}

void turnRight() {
  // Turn right when the ass of the bot is facing you
  motors.rightMotor(-222);
  motors.leftMotor(12);
}

void turnLeft() {
  // Turn left when the ass of the bot is facing you
  motors.leftMotor(222);
  motors.rightMotor(-12);
}

void checkState() {
  switch(machineState){
    case advance:
      Serial.println("forward");
      forward();
    break;
    case left:
      Serial.println("left");
      turnLeft();
    break;
    case right:
      Serial.println("right");
      turnRight();
    break;
    case reverseLeft:
      Serial.println("Left reverse");
      backwardsLeft();
    break;
    case reverseRight:
      Serial.println("Right reverse");
      backwardsRight();
    break;
  }
}

void echoCollision() {
  for (uint8_t i =0; i < SONAR_NUM; i++) {
      delay(50); // Waiting 50ms between pings is about 20 pings/sec. 29ms should be the shortest delay between pings.
      Serial.print(i);
      Serial.print("=");
      Serial.print(sonar[i].ping_cm());
      Serial.print("cm ");
  }
  Serial.println();
  if((sonar[0].ping_cm() > sonar[1].ping_cm()) && (sonar[0].ping_cm() <= 18) && (sonar[1].ping_cm() <= 18) && (sonar[0].ping_cm() != 0) && (sonar[1].ping_cm() != 0)){
    machineState = reverseLeft;
    Serial.println("backwards right");
  }
  else if((sonar[1].ping_cm() > sonar[0].ping_cm()) && (sonar[0].ping_cm() <= 18) && (sonar[1].ping_cm() <= 18) && (sonar[0].ping_cm() != 0) && (sonar[1].ping_cm() != 0)){
    machineState = reverseRight;
    Serial.println("backwards left");
  }
  else if((sonar[0].ping_cm() <= 18) && (sonar[0].ping_cm() != 0) && (sonar[1].ping_cm() != 0)){
    machineState = right;
    Serial.println(machineState);
  }
  else if((sonar[1].ping_cm() <= 18) && (sonar[0].ping_cm() != 0) && (sonar[1].ping_cm() != 0)){
    machineState = left;
    Serial.println(machineState);
  }
  else {
    machineState = advance;
    Serial.println(machineState);
  }
}

void findLight() {
  leftRes = analogRead(LEFTPHOTORESISTOR);
  rightRes = analogRead(RIGHTPHOTORESISTOR);

  if(leftRes > ambientLight) {
    Serial.println("left is higher");
  }
  else if(leftRes > ambientLight) {
    Serial.println("left is higher");
  }
}

void photoResistorValues() {
  leftRes = analogRead(LEFTPHOTORESISTOR);
  rightRes = analogRead(RIGHTPHOTORESISTOR);
  
  Serial.print("Left photoresistor value: ");
  Serial.println(leftRes);
  Serial.print("Right photoresistor value: ");
  Serial.println(rightRes);
}
