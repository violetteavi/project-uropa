#include "Servo.h"
//#include "MPU9250.h"

//MPU9250 IMU(Wire,0x68);

int leftMotorPin = 11;
int rightMotorPin = 12;
int enablePin = 2;
int ledPin = 5;

int status;
Servo ESCL;//Left side motor
Servo ESCR;//Right side motor

int maxSpeed = 179;
int period = 10000;
bool isActive = false;
bool enabled = false;
int startTime;
  
void setup() {
  //Serial.begin(9600);
  ESCL.attach(leftMotorPin);//Left side ESC signal pin10
  ESCR.attach(rightMotorPin);//Right side ESC signal pin9
  delay(100);
  //Serial.println("Ready");
  pinMode(enablePin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  startTime = millis();
  ESCL.write(0);
  ESCR.write(0);
  delay(100);
}

void loop(){

  bool prevEnabled = enabled;
  enabled = (true); //digitalRead(enablePin) == HIGH
  if(enabled and !prevEnabled)
  {
      isActive = true;
      startTime = millis();
  }
  
  if(enabled)
  {
    enableMotors(isActive);
    int deltaTime = millis() - startTime;
    if(deltaTime > period)
    {
      isActive = !isActive;
      startTime = millis();
    }
  }
  else
  {
      isActive = false;
      enableMotors(false);
  }
}

void enableMotors(bool active)
{
  if(active)
  {
      ESCL.write(maxSpeed); // COMMENT THIS OUT TO TURN LEFT    (BOTH UNCOMMENTED IS FULL FWD)
      ESCR.write(maxSpeed); // COMMENT THIS OUT TO TURN RIGHT
      digitalWrite(ledPin, HIGH);
  }
  else
  {
      ESCL.write(55);
      ESCR.write(55);
      digitalWrite(ledPin, LOW);
  }
}
