#include <TimedAction.h>
#include <SPI.h>
#include "PixyReader.h"
#include "Servo.h"
//#include "MPU9250.h"
#include <ESC.h>

#define PWM_MAXB (1100) //backward max 
#define PWM_MINB (1460) //backward min 
#define PWM_MAXF (1900) //forward max 
#define PWM_MINF (1530) //forward min 
#define PWM_STOP (1500) // Stop
//MPU9250 IMU(Wire,0x68);

//int leftMotorPin = 11;
//int rightMotorPin = 12;
int enablePin = 50;
int ledPin = 53;
int groundPin = 36;
double powerProportion = 0.4;

//MPU9250 IMU(Wire,0x68);

ESC myESCL (22, PWM_MAXB, PWM_MAXF, 500);//Left side motor
ESC myESCR (23, PWM_MAXB, PWM_MAXF, 500);//Right side motor

int period = 3000;
bool enabled = false;
int startTime;
int state = 0;
// methods to be run periodically
void updateSensors();
void printPixyVals();

// interfaces encapsulated for code hygiene
PixyReader* pixyReader;

// Timers to run various control logics
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction pixyPrintAction = TimedAction(60, printPixyVals);
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("Setup running.");
  
  SPI.begin();
  Serial.println("SPI Active.");
  pixyReader = new PixyReader();
  Serial.println("Pixy Active.");
  
  Serial.println("Setup finished.");
  myESCL.arm();//Left side ESC signal pin11
  myESCR.arm();//Right side ESC signal pin9
  
  pinMode(enablePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(groundPin, OUTPUT);

  digitalWrite(ledPin, HIGH);
  digitalWrite(groundPin, LOW);
  startTime = millis();
}

void loop(){
   bool prevEnabled = enabled;
  enabled = true;//(digitalRead(enablePin) == HIGH); //
  if(enabled and !prevEnabled)
  {
      state = 0;
      startTime = millis();
  }
  
  if(enabled)
  {
    switch(state)
    {
      case 0:
        setMotorSpeeds(powerProportion, powerProportion);
        break;
      case 1:
        setMotorSpeeds(-powerProportion, -powerProportion);
        break;
      case 2:
        setMotorSpeeds(0, 0);
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
      //setMotorSpeeds(0, 0);
      state = 0;
  }
  sensorReadAction.check();
  pixyPrintAction.check();
}

void updateSensors()
{
  pixyReader->updatePixyVals();
}

void printPixyVals()
{
  if(pixyReader->updatesSinceLastSuccess == 0)
  {
    Serial.print("propAcross:\t");
    Serial.print(pixyReader->propAcross);
    Serial.print("\tpropDown:\t");
    Serial.print(pixyReader->propDown);
    Serial.print("\tmaxDim:\t");
    Serial.print(pixyReader->maxBound);
    Serial.print("\tDist:\t");
    Serial.print(pixyReader->distAway);
    /*
    Serial.print("\tx:\t");
    Serial.print(pixyReader->latestBlock.x);
    Serial.print("\ty:\t");
    Serial.print(pixyReader->latestBlock.y);
    Serial.print("\twid:\t");
    Serial.print(pixyReader->latestBlock.width);
    Serial.print("\thei:\t");
    Serial.print(pixyReader->latestBlock.height);
    */
    Serial.println();
  }
}
void setMotorSpeeds(float leftProportion, float rightProportion)
{
  int leftMotorPWM = proportionToPWM(leftProportion);
  int rightMotorPWM = proportionToPWM(rightProportion);
  myESCL.speed(leftMotorPWM); 
  myESCR.speed(rightMotorPWM); 
  sensorReadAction.check();
  pixyPrintAction.check();
  if(leftMotorPWM != PWM_STOP || rightMotorPWM != PWM_STOP)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);
}

int proportionToPWM(float proportion)
{
  if(proportion > 0)
  {
    int pwmF = (int)(proportion*(PWM_MAXF-PWM_MINF) + PWM_MINF);
    return pwmF;
  }
  else if(proportion < 0)
  {
    proportion *= -1;
    int pwmB = (int)(proportion*(PWM_MAXB-PWM_MINB) + PWM_MINB);
    return pwmB;
  }
  else
  {
    return PWM_STOP;
  }
}
