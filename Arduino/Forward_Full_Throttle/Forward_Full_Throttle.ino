#include "Servo.h"
//#include "MPU9250.h"
#include <ESC.h>
#define SPEED_MAXB (1100) //backward max 
#define SPEED_MINB (1460) //backward max 
#define SPEED_MAXF (1900) //forward max 
#define SPEED_MINF (1530) //foraward max 
#define SPEED_STOP (1500) // Stop
//MPU9250 IMU(Wire,0x68);

//int leftMotorPin = 11;
//int rightMotorPin = 12;
int enablePin = 50;
int ledPin = 52;
int groundPin = 53;
double powerProportion = 0.4;
int status;

//MPU9250 IMU(Wire,0x68);

ESC myESCL (11, SPEED_MAXB, SPEED_MAXF, 1500);//Left side motor
ESC myESCR (12, SPEED_MAXB, SPEED_MAXF, 1500);//Right side motor
//int maxSpeed = 90;
int period = 3000;
bool isActive = false;
bool enabled = false;
int startTime;
int state = 0;
  
void setup() {
  //Serial.begin(9600);
  myESCL.arm();//Left side ESC signal pin10
  myESCR.arm();//Right side ESC signal pin9
  
  //Serial.println("Ready");
  pinMode(enablePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(groundPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(groundPin, LOW);
  startTime = millis();
  //delay(5000);

}

void loop(){
  //myESCL.arm();//Left side ESC signal pin10
  //myESCR.arm();//Right side ESC signal pin9
  bool prevEnabled = enabled;
  enabled = (digitalRead(enablePin) == HIGH); //
  if(enabled and !prevEnabled)
  {
      isActive = true;
      startTime = millis();
  }
  
  if(enabled)
  {
    switch(state)
    {
      case 0:
        setMotorSpeed(powerProportion);
        break;
      case 1:
        setMotorSpeed(-powerProportion);
        break;
      case 2:
        setMotorSpeed(0);
        break;
    }
    
    int deltaTime = millis() - startTime;
    if(deltaTime > period)
    {
      state = (state + 1) % 3;
      startTime = millis();
    }
  }
  else
  {
      isActive = false;
      setMotorSpeed(0);
      state = 0;
  }
}

void setMotorSpeed(float motorSpeed)
{
  if(motorSpeed > 0)
  {
      int motorPowerF = (int)(motorSpeed*(SPEED_MAXF-SPEED_MINF) + SPEED_MINF);
      myESCL.speed(motorPowerF); // COMMENT THIS OUT TO TURN LEFT    (BOTH UNCOMMENTED IS FULL FWD)
      myESCR.speed(motorPowerF); // COMMENT THIS OUT TO TURN RIGHT
      digitalWrite(ledPin, HIGH);
      delay(10);
  }
  else if(motorSpeed < 0)
  {
      motorSpeed *= -1;
      int motorPowerB = (int)(motorSpeed*(SPEED_MAXB-SPEED_MINB) + SPEED_MINB);
      myESCL.speed(motorPowerB); // COMMENT THIS OUT TO TURN LEFT    (BOTH UNCOMMENTED IS FULL FWD)
      myESCR.speed(motorPowerB); // COMMENT THIS OUT TO TURN RIGHT
      digitalWrite(ledPin, HIGH);
      delay(10);
  }
  else if(motorSpeed == 0)
  {
      myESCL.speed(SPEED_STOP);
      myESCR.speed(SPEED_STOP);
      digitalWrite(ledPin, LOW);
      delay(10);
  }
}
