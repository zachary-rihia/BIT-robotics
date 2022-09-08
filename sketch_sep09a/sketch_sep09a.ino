const int leftPhotoresistor = A2;
const int rightPhotoresistor = A3;
const int leftEcho = A0;
const int rightEcho = A7;
const int leftTrig = A1;
const int rightTrig = A6;

int leftRes;
int rightRes;
int leftDistance;
int rightDistance;
long leftDuration;
long rightDuration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftTrig, OUTPUT);
  pinMode(rightTrig, OUTPUT);
  pinMode(leftEcho, INPUT);
  pinMode(rightEcho, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftRes = analogRead(leftPhotoresistor);
  rightRes = analogRead(rightPhotoresistor);

  echo();
  
  Serial.print("Left photoresistor value: ");
  Serial.println(leftRes);
  Serial.print("Right photoresistor value: ");
  Serial.println(rightRes);
  Serial.print("Left distance: ");
  Serial.print(leftDistance);
  Serial.println(" cm");
  Serial.print("Right distance: ");
  Serial.print(rightDistance);
  Serial.println(" cm");
  delay(500);
}

void echo() {
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
}
