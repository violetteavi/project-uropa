/*
||
|| @file ThreeExamplesAtOnce.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | This sketch blinks an LED as Blink
|| |             sets a led on or off according to serial buffer as PhysicalPixel
|| |             prints the ascii table as ASCIITable
|| #
||
*/
 
#include <TimedAction.h>
#include "PixyReader.h"

// methods to be run periodically
void updateSensors();
void printPixyVals();

// interfaces encapsulated for code hygiene
PixyReader pixyReader;

// Timers to run various control logics
TimedAction pixyReadAction = TimedAction(30, updateSensors);
TimedAction pixyPrintAction = TimedAction(1000, printPixyVals);
 
 
void setup(){
  Serial.begin(9600);
}

void loop(){
  pixyReadAction.check();
  pixyPrintAction.check();
}

void updateSensors()
{
  pixyReader.updatePixyVals();
}

void printPixyVals()
{
  if(pixyReader.updatesSinceLastSuccess == 0)
  {
    Serial.print("Biggest bounding box had propAcross: ");
    Serial.print(pixyReader.propAcross);
    Serial.print("\tpropDown: ");
    Serial.print(pixyReader.propDown);
    Serial.print("\tmaxDim: ");
    Serial.print(pixyReader.maxBound);
    Serial.println();
  }
  else
  {
    Serial.println("No pixy bounding boxes found!");
  }
}

