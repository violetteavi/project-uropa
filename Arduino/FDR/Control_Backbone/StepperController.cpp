#include "StepperController.h"

StepperController::StepperController(uint8_t CSPin, int bottomSwitchPin, int topSwitchPin)
{
  Serial.println("Initializing stepper controller.");
  driver.setChipSelectPin(CSPin);

  // Give the driver some time to power up.
  delay(2);
  Serial.println("Stepper initialized.");

  // Reset the driver to its default settings and clear latched status
  // conditions.
  driver.resetSettings();
  driver.clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  // for most applications, and we find that it usually works well.
  driver.setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  driver.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max

  // Set the number of microsteps that correspond to one full step.
  driver.setStepMode(HPSDStepMode::MicroStep1);

  // Set the default direction to forward
  driver.setDirection(1);

  Serial.println("Stepper settings sent.");
  // Enable the motor outputs.
  driver.enableDriver();
  Serial.println("Stepper enabled.");

  pinMode(bottomSwitchPin, INPUT);
  pinMode(topSwitchPin, INPUT);
  chipSelect = CSPin;
  bottomSwitch = bottomSwitchPin;
  topSwitch = topSwitchPin;
  Serial.println("Stepper limit switches enabled.");
}

bool StepperController::updatePulseApplication()
{
  long positionError = targetStepCount - currentStepCount;
  if(positionError > 0)
  {
    if(digitalRead(topSwitch) == HIGH) return false;
    setDirectionIfNecessary(true);
    driver.step();
    currentStepCount++;
    return true;
  }
  if(positionError < 0)
  {
    if(digitalRead(bottomSwitch) == HIGH) return false;
    setDirectionIfNecessary(false);
    driver.step();
    currentStepCount--;
    return true;
  }
}


void StepperController::setDirectionIfNecessary(bool forward)
{
  if(forward)
  {
    if(driver.getDirection() != 1) 
    {
      driver.setDirection(1);
    }
  }
  else
  {
    if(driver.getDirection() != 0) 
    {
      driver.setDirection(0);
    }
  }
}
