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
TimedAction pixyPrintAction = TimedAction(60, printPixyVals);
 
 
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
