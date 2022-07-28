
#include <RedBot.h>  // This line "includes" the library into your sketch.

RedBotMotors motors; // Instantiate the motor control object.

void setup()
{
//squareSpiral();
}

void loop()
{
  squareSpiral();
  delay(5000);
  zigzag();
  delay(5000);
  lawnMower();
  delay(5000);
  circle();
}

void forward(){
  // Forward
  motors.rightMotor(111);
  motors.leftMotor(-107);
}

void turnRight(){
  // Turn right when the ass of the bot is facing you
  motors.rightMotor(220);
  motors.leftMotor(-24);
}

void turnLeft() {
  motors.leftMotor(-220);
  motors.rightMotor(24);
}

void squareSpiral(){
  int delayCounter = 500;

  for (int i = 0; i <= 4; i++) {
    forward();
    delay(delayCounter);
    delayCounter += 200;
    turnRight();
    delay(500);
  }
  motors.brake();
}

void zigzag() {
  bool adjust = true;
  
  if (adjust == true) {
    motors.leftMotor(-200);
    motors.rightMotor(12);
    adjust = !adjust;
    delay(200);
    forward();
    delay(800);
  }
  
  for (int i = 0; i <= 4; i++) {
      motors.leftMotor(-222);
      motors.rightMotor(6);
      delay(550);
      forward();
      delay(1000);
      motors.rightMotor(222);
      motors.leftMotor(6);
      delay(550);
      forward();
      delay(1000);
  }
}

void lawnMower() { 
   for (int i = 0; i <= 3; i++) {
    forward();
    delay(1500);
    turnRight();
    delay(500);
    forward();
    delay(700);
    turnRight();
    delay(500);
    forward();
    delay(1500);
    turnLeft();
    delay(500);
    forward();
    delay(700);
    turnLeft();
    delay(500);
  }
}

void circle() {
  motors.rightMotor(150);
  motors.leftMotor(-100);
  delay(500);
}
