#include <TimedAction.h>
#include <SPI.h>
#include "PixyReader.h"
#include "AccelerometerReader.h"
#include "StepperController.h"
#include "PropellerController.h"
//#include <ESC.h>

// methods to be run periodically
void updateSensors();
void updateSteppers();
void updateStepperSetpoint();
void printPixyVals();
void updateProps();
void updatePropSetpoint();

// interfaces encapsulated for code hygiene
PixyReader* pixyReader;
AccelerometerReader* accelerometerReader;
StepperController* stepperController1;
StepperController* stepperController2;
StepperController* stepperController3;
PropellerController* rightProp;
PropellerController* leftProp;

// Timers to run various control logics
TimedAction stepperUpdateAction = TimedAction(2, updateSteppers);
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction updatePropAction = TimedAction(10, updateProps);
TimedAction pixyPrintAction = TimedAction(1000, printPixyVals);
TimedAction updateStepperSetpointAction= TimedAction(1000, updateStepperSetpoint);
TimedAction updatePropSetpointAction= TimedAction(6000, updatePropSetpoint);
 
 
void setup(){
  Serial.begin(9600);
  //Serial.println("Setup running.");
  //SPI.begin();
  //Serial.println("SPI Active.");

  //pixyReader = new PixyReader();
  //Serial.println("Pixy Active.");
  //accelerometerReader = new AccelerometerReader();
  //Serial.println("Accelerometer Active.");
  ///*
  stepperController1 = new StepperController(9);
  delay(100);
  stepperController2 = new StepperController(10);
  delay(100);
  /*
  stepperController3 = new StepperController(11);
  delay(100);
  //stepperController4 = new StepperController(12);
  Serial.println("Stepper Driver Active.");
  */
  rightProp = new PropellerController(18);
  Serial.println("Setup finished.");
  delay(2000);
}

void loop(){
  stepperUpdateAction.check();
  //sensorReadAction.check();
  //pixyPrintAction.check();
  updateStepperSetpointAction.check();
  //updatePropAction.check();
  //updatePropSetpointAction.check();
}

void updateSensors()
{
  //pixyReader->updatePixyVals();
  accelerometerReader->updateAccelerometerVals();
}

void updateSteppers()
{
  stepperController1->updatePulseApplication();
  stepperController2->updatePulseApplication();
  //stepperController3->updatePulseApplication();
  //stepperController4->updatePulseApplication();
}

void updateStepperSetpoint()
{
  if(stepperController1->targetStepCount == 0)
  {
    stepperController1->targetStepCount = 400;
    stepperController2->targetStepCount = 400;
    //stepperController3->targetStepCount = -400;
    //stepperController4->targetStepCount = 400;
  }
  else
  {
    stepperController1->targetStepCount = 0;
    stepperController2->targetStepCount = 0;
    //stepperController3->targetStepCount = 0;
    //stepperController4->targetStepCount = 0;
  }
}

void updateProps()
{
  //leftProp->updateVelocity();
  rightProp->updateVelocity();
}

void updatePropSetpoint()
{
  if(rightProp->targetProportion != 0.4)
  {
    //leftProp->targetProportion = 1;
    rightProp->targetProportion = 0.4;
  }
  else
  {
    //leftProp->targetProportion = -1;
    rightProp->targetProportion = -0.4;
  }
}

void printPixyVals()
{
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
  }
  */
  
  //{
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
//  */
}
