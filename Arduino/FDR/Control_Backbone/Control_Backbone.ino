#include <TimedAction.h>
#include "PixyReader.h"
#include "AccelerometerReader.h"

// methods to be run periodically
void updateSensors();
void printPixyVals();

// interfaces encapsulated for code hygiene
PixyReader* pixyReader;
AccelerometerReader* accelerometerReader;

// Timers to run various control logics
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction pixyPrintAction = TimedAction(1000, printPixyVals);
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("Setup running.");

  pixyReader = new PixyReader();
  accelerometerReader = new AccelerometerReader();
  
  Serial.println("Setup finished.");
}

void loop(){
  sensorReadAction.check();
  pixyPrintAction.check();
}

void updateSensors()
{
  pixyReader->updatePixyVals();
  accelerometerReader->updateAccelerometerVals();
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

