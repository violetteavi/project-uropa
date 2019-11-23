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
//AccelerometerReader* accelerometerReader;
StepperController* stepperController1;
StepperController* stepperController2;
StepperController* stepperController3;

// Timers to run various control logics
TimedAction stepperUpdateAction = TimedAction(2, updateSteppers);
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction pixyPrintAction = TimedAction(1000, printPixyVals);
TimedAction updateStepperSetpointAction= TimedAction(1000, updateStepperSetpoint);
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("Setup running.");
  SPI.begin();
  Serial.println("SPI Active.");

  pixyReader = new PixyReader();
  Serial.println("Pixy Active.");
  //accelerometerReader = new AccelerometerReader();
  //Serial.println("Accelerometer Active.");
  stepperController1 = new StepperController(9);
  stepperController2 = new StepperController(10);
  stepperController3 = new StepperController(11);
  Serial.println("Stepper Driver Active.");
  
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
  //accelerometerReader->updateAccelerometerVals();
}

void updateSteppers()
{
  stepperController1->updatePulseApplication();
  stepperController2->updatePulseApplication();
  stepperController3->updatePulseApplication();
}

void updateStepperSetpoint()
{
  if(stepperController1->targetStepCount == 0)
  {
    stepperController1->targetStepCount = 200;
    stepperController2->targetStepCount = 200;
    stepperController3->targetStepCount = 200;
  }
  else
  {
    stepperController1->targetStepCount = 0;
    stepperController2->targetStepCount = 0;
    stepperController3->targetStepCount = 0;
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

  /*
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
  */
}
