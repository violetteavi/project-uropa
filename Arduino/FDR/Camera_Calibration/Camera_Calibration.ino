#include <TimedAction.h>
#include <SPI.h>
#include "PixyReader.h"

// methods to be run periodically
void updateSensors();
void printPixyVals();

// interfaces encapsulated for code hygiene
PixyReader* pixyReader;

// Timers to run various control logics
TimedAction sensorReadAction = TimedAction(30, updateSensors);
TimedAction pixyPrintAction = TimedAction(1000, printPixyVals);
 
 
void setup(){
  Serial.begin(9600);
  Serial.println("Setup running.");
  
  SPI.begin();
  Serial.println("SPI Active.");
  pixyReader = new PixyReader();
  Serial.println("Pixy Active.");
  
  Serial.println("Setup finished.");
}

void loop(){
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
    Serial.print("Biggest bounding box had propAcross:\t");
    Serial.print(pixyReader->propAcross);
    Serial.print("\tpropDown:\t");
    Serial.print(pixyReader->propDown);
    Serial.print("\tmaxDim:\t");
    Serial.print(pixyReader->maxBound);
    Serial.println();
  }
}
