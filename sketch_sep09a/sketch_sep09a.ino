#include <RedBot.h>  // This line "includes" the library into your sketch.
#include <NewPing.h> // https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
#include <LightDependentResistor.h> // https://github.com/QuentinCG/Arduino-Light-Dependent-Resistor-Library

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
  findLight();
  checkState();
}

void forward() {
  // Forward
  motors.rightMotor(-111);
  motors.leftMotor(105);
}

void backwardsRight() {
  motors.rightMotor(80);
  motors.leftMotor(-220);
}

void backwardsLeft() {
  motors.rightMotor(220);
  motors.leftMotor(-80);
}

void turnRight() {
  // Turn right when the ass of the bot is facing you
  motors.rightMotor(-201);
  motors.leftMotor(50);
}

void turnLeft() {
  // Turn left when the ass of the bot is facing you
  motors.leftMotor(201);
  motors.rightMotor(-50);
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
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.print("cm ");
  }
  Serial.println();
  
  if(sonar[0].ping_cm() <= 6){
    machineState = reverseRight;
    checkState();
    delay(600);
    machineState = advance;
    delay(250);
  }
  else if(sonar[1].ping_cm() <= 6){
    machineState = reverseLeft;
    checkState();
    delay(600);
    machineState = advance;
    delay(250);
  }
  else {
    machineState = advance;
  }
}

void findLight() {
  leftRes = analogRead(LEFTPHOTORESISTOR);
  rightRes = analogRead(RIGHTPHOTORESISTOR);

  int amVal = (sqrt((ambientLight + ambientLight) * 2));
  int leftVal = (sqrt((ambientLight + leftRes) * 2));
  int rightVal = (sqrt((ambientLight + rightRes) * 2));
  
  if((leftVal > amVal) && ((leftVal - 1) > rightVal)) {
    Serial.println("left is higher");
    machineState = left;
  }else {
    echoCollision();
  }
  
  if((rightVal > amVal) && (rightVal > (leftVal - 1))) {
    Serial.println("right is higher");
    machineState = right;
  }
  else {
    echoCollision();
  }
}
