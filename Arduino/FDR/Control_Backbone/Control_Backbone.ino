#include <TimedAction.h>
#include <SPI.h>
#include "PixyReader.h"
#include "AccelerometerReader.h"
#include "StepperController.h"

// methods to be run periodically
void updateSensors();
void updateSteppers();
void updateStepperSetpoint();
void printPixyVals();

// interfaces encapsulated for code hygiene
PixyReader* pixyReader;
AccelerometerReader* accelerometerReader;
StepperController* stepperController;

// Timers to run various control logics
TimedAction stepperUpdateAction = TimedAction(2, updateSteppers);
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction pixyPrintAction = TimedAction(1000, printPixyVals);
TimedAction updateStepperSetpointAction= TimedAction(3000, updateStepperSetpoint);
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("Setup running.");
  SPI.begin();

  pixyReader = new PixyReader();
  accelerometerReader = new AccelerometerReader();
  stepperController = new StepperController(8);
  
  Serial.println("Setup finished.");
}

void loop(){
  stepperUpdateAction.check();
  sensorReadAction.check();
  pixyPrintAction.check();
  updateStepperSetpointAction.check();
}

void updateSensors()
{
  pixyReader->updatePixyVals();
  accelerometerReader->updateAccelerometerVals();
}

void updateSteppers()
{
  stepperController->updatePulseApplication();
}

void updateStepperSetpoint()
{
  if(stepperController->targetStepCount == 0)
  {
    stepperController->targetStepCount = 2000;
  }
  else
  {
    stepperController->targetStepCount = 0;
  }
}

void printPixyVals()
{
  if(pixyReader->updatesSinceLastSuccess == 0)
  {
    Serial.print("Biggest bounding box had propAcross: ");
    Serial.print(pixyReader->propAcross);
    Serial.print("\tpropDown: ");
    Serial.print(pixyReader->propDown);
    Serial.print("\tmaxDim: ");
    Serial.print(pixyReader->maxBound);
    Serial.println();
  }
  else
  {
    Serial.println("No pixy bounding boxes found!");
  }

  
  if(!accelerometerReader->errorFlag)
  {
    Serial.print("Acceleromater yields\tpitchAngle: ");
    Serial.print(accelerometerReader->pitchAngle * 180 / 3.14);
    Serial.print("\trollAngle: ");
    Serial.print(accelerometerReader->rollAngle * 180 / 3.14);
    Serial.print("\tdownAcceleration: ");
    Serial.print(accelerometerReader->downAcceleration);
    Serial.println();
  }
  else
  {
    Serial.println("Accelerometer reading failed!");
  }
}
