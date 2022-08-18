#include <RedBot.h>
RedBotSensor left = RedBotSensor(A3);   // initialize a left sensor object on A3
RedBotSensor center = RedBotSensor(A6); // initialize a center sensor object on A6
RedBotSensor right = RedBotSensor(A7);  // initialize a right sensor object on A7

#define LEFTSPEED 70  // sets the nominal speed. Set to any number from 0 - 255.
#define RIGHTSPEED 77  // sets the nominal speed. Set to any number from 0 - 255.
#define DELAYCOUNTER 500 // sets the nominal delay 

RedBotMotors motors;
const int threshold = 700;

int leftSpeed;   // variable used to store the leftMotor speed
int rightSpeed;  // variable used to store the rightMotor speed
int impede;     // varibale used to increase the delay

void setup()
{
    Serial.begin(9600);
    Serial.println("Welcome to experiment 6.2 - Line Following");
    Serial.println("------------------------------------------");
    delay(2000);
    Serial.println("IR Sensor Readings: ");
    delay(500);
}

void loop()
{
    if(center.read() >= threshold){
      Serial.print(left.read());
      Serial.print("\t");  // tab character
      Serial.print(center.read());
      Serial.print("\t");  // tab character
      Serial.print(right.read());
      Serial.println();
    }
//    findLine();
    follow();
    advance();
}

void advance() {
    motors.leftMotor(leftSpeed);
    motors.rightMotor(rightSpeed);
}

void follow()  {
    // if all sensors are over threshold then move forward
    if(left.read() >= threshold && center.read() >= threshold && right.read() >= threshold)
    {
        leftSpeed = LEFTSPEED; 
        rightSpeed = -RIGHTSPEED;
    }

    // if the left sensor less than the threshold then turn right
    else if(left.read() < threshold && center.read() >= threshold && right.read() >= threshold)
    {
        leftSpeed = LEFTSPEED + 50;
        rightSpeed = -(RIGHTSPEED - 50);
    }

    // if the right sensor less than the threshold then turn left
    else if(left.read() >= threshold && center.read() >= threshold && right.read() < threshold)
    {
        leftSpeed = LEFTSPEED - 50;
        rightSpeed = -(RIGHTSPEED + 50);
    }
    else{
      findLine();
    }
}

void findLine(){
  impede = DELAYCOUNTER;
  if(center.read() < threshold && right.read() < threshold){
    leftSpeed = LEFTSPEED - 50;
    rightSpeed = -(RIGHTSPEED + 50);
    delay(impede);
    impede + 100;
  }
  else if(left.read() < threshold && center.read() < threshold){
    leftSpeed = -(LEFTSPEED + 50);
    rightSpeed = RIGHTSPEED - 50;
    delay(impede);
    impede + 100;
  }
}
