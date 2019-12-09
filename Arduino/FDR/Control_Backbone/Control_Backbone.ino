#include <TimedAction.h>
#include <SPI.h>
#include <ESC.h>
#include "PixyReader.h"
#include "AccelerometerReader.h"
#include "StepperController.h"
#include "PropellerController.h"
#include "BuoyancyController.h"

// methods to be run periodically
void updateSensors();
void readSerialForBuoyancy();
void updateSteppers();
void updateStepperSetpoint();
void printPixyVals();
void updateProps();
void updatePropSetpoint();

// interfaces encapsulated for code hygiene
PixyReader* pixyReader;
//AccelerometerReader* accelerometerReader;
BuoyancyController* buoyancyController;
PropellerController* rightProp;
PropellerController* leftProp;

// Timers to run various control logics
int stepperDelayUs = 1500;
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction updatePropAction = TimedAction(30, updateProps);
TimedAction pixyPrintAction = TimedAction(3000, printPixyVals);
TimedAction updateStepperSetpointAction= TimedAction(3000, updateStepperSetpoint);
TimedAction updatePropSetpointAction= TimedAction(6000, updatePropSetpoint);
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("Setup running.");
  SPI.begin();
  Serial.println("SPI Active.");
 
  //pixyReader = new PixyReader();
  //Serial.println("Pixy Active.");
  //accelerometerReader = new AccelerometerReader();
  //Serial.println("Accelerometer Active.");
  ///*
//  stepperController1 = new StepperController(9,4,6);
//  delay(100);
//  Serial.println("Stepper 1 active.");
//  stepperController2 = new StepperController(10,3,5);
//  delay(100);
//  Serial.println("Stepper 2 active.");
  
  delay(100);
  StepperController* frontLeft = new StepperController(9,4,6);
  //frontLeft->targetStepCount = 400;
  delay(100);
  StepperController* backLeft = new StepperController(10,3,5);
  //backLeft->targetStepCount = 400;
  delay(100);
  StepperController* frontRight = new StepperController(11,7,2);
  //frontRight->targetStepCount = 400;
  delay(100);
  StepperController* backRight = new StepperController(12,8,13);
  //backRight->targetStepCount = 400;
  delay(100);
  buoyancyController = new BuoyancyController(frontLeft, backLeft, frontRight, backRight);
  Serial.println("Steppers active.");
  Serial.println("Calibrating...");
  buoyancyController->calibrate();
  Serial.println("Going to neutral..");
  buoyancyController->setAllToNeutral();
 // stepperController4 = new StepperController(12,34,32);
 // Serial.println("Stepper 4 active.");
  
  //rightProp = new PropellerController(18);
  Serial.println("Setup finished.");
  delay(2000);
}

void loop(){
  while(true)
  {
    updateSteppers();
    sensorReadAction.check();
    pixyPrintAction.check();
    //updateStepperSetpointAction.check();
    //updatePropAction.check();
    //updatePropSetpointAction.check();
    delayMicroseconds(stepperDelayUs);
  }
}

void updateSensors()
{
  //pixyReader->updatePixyVals();
  //accelerometerReader->updateAccelerometerVals();
  readSerialForBuoyancy();
}

void readSerialForBuoyancy()
{
  long stepDelta = 0.1*BuoyancyController::TRAVEL_LENGTH_STEPS;
  if (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if(incomingByte == -1) return;
    char parsedByte = (char) incomingByte;
    switch(parsedByte)
    {
      case 'L':
        buoyancyController->applyRoll(stepDelta);
        break;
      case 'R':
        buoyancyController->applyRoll(-stepDelta);
        break;
      case 'F':
        buoyancyController->applyPitch(stepDelta);
        break;
      case 'B':
        buoyancyController->applyPitch(-stepDelta);
        break;
      case 'U':
        buoyancyController->applyBuoyancy(stepDelta);
        break;
      case 'D':
        buoyancyController->applyBuoyancy(-stepDelta);
        break;
    }
  }
}

void updateSteppers()
{
  buoyancyController->updatePulseApplication();
  //stepperController1->updatePulseApplication();
  //stepperController2->updatePulseApplication();
  //stepperController3->updatePulseApplication();
  //stepperController4->updatePulseApplication();
}

void updateStepperSetpoint()
{
  /*
  if(stepperController3->targetStepCount == 0)
  {
    //stepperController1->targetStepCount = 1000;
    //stepperController2->targetStepCount = 1000;
    stepperController3->targetStepCount = 1000;
    //stepperController4->targetStepCount = 1000;
  }
  else
  {
    //stepperController1->targetStepCount = 0;
    //stepperController2->targetStepCount = 0;
    stepperController3->targetStepCount = 0;
    //stepperController4->targetStepCount = 0;
  }
  Serial.println("Stepper setpoints updated!");
  */
}

void updateProps()
{
  leftProp->updateVelocity();
  rightProp->updateVelocity();
}

void updatePropSetpoint()
{
  if(rightProp->targetProportion != 0.4)
  {
    leftProp->targetProportion = 1;
    rightProp->targetProportion = 0.4;
  }
  else
  {
    leftProp->targetProportion = -1;
    rightProp->targetProportion = -0.4;
  }
}

void printPixyVals()
{
  Serial.print("FrontLeft: ");
  Serial.print(buoyancyController->frontLeft->currentStepCount);
  Serial.print(" BackLeft: ");
  Serial.print(buoyancyController->backLeft->currentStepCount);
  Serial.print(" FrontRight: ");
  Serial.print(buoyancyController->frontRight->currentStepCount);
  Serial.print(" BackRight: ");
  Serial.print(buoyancyController->backRight->currentStepCount);
  Serial.println();
  
  /*
  if(pixyReader->updatesSinceLastSuccess == 0)
  {
    Serial.print("Biggest bounding box had propAcross:\t");
    Serial.print(pixyReader->propAcross);
    Serial.print("\tpropDown:\t");
    Serial.print(pixyReader->propDown);
    Serial.print("\tmaxDim:\t");
    Serial.print(pixyReader->maxBound);
    Serial.println();
  }
  else
  {
    Serial.println("No pixy bounding boxes found!");
  } */
  
  
  /*{
    Serial.print("Acceleromater yields\tpitchAngle: ");
    Serial.print(accelerometerReader->pitchAngle * 180 / 3.14);
    Serial.print("\trollAngle: ");
    Serial.print(accelerometerReader->rollAngle * 180 / 3.14);
    Serial.print("\tdownAcceleration: ");
    Serial.print(accelerometerReader->downAcceleration);
    Serial.println();
  //}
  if(accelerometerReader->errorStatus < 0)
  {
    Serial.print("Accelerometer reading failed! Status: ");
    Serial.println(accelerometerReader->errorStatus);
  }
  */
}
