#include "StepperController.h"

StepperController::StepperController(uint8_t CSPin, int bottomSwitchPin, int topSwitchPin)
{
  driver.setChipSelectPin(CSPin);

  // Give the driver some time to power up.
  delay(2);

  // Reset the driver to its default settings and clear latched status
  // conditions.
  driver.resetSettings();
  driver.clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  // for most applications, and we find that it usually works well.
  //sd.setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  driver.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max

  // Set the number of microsteps that correspond to one full step.
  driver.setStepMode(HPSDStepMode::MicroStep1);

  // Enable the motor outputs.
  driver.enableDriver();

  pinMode(bottomSwitchPin, INPUT);
  pinMode(topSwitchPin, INPUT);
  chipSelect = CSPin;
  bottomSwitch = bottomSwitchPin;
  topSwitch = topSwitchPin;
}

bool StepperController::updatePulseApplication()
{
  int positionError = currentStepCount - targetStepCount;
  if(abs(positionError) <= DEAD_ZONE) return false;
  bool switchHit = digitalRead(bottomSwitch) == HIGH || digitalRead(topSwitch) == HIGH;
  if(switchHit) return false;
  if(positionError < 0)
  {
    setDirectionIfNecessary(true);
    driver.step();
    currentStepCount++;
    return true;
  }
  if(positionError > 0)
  {
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
    driver.setDirection(1);
  }
  else
  {
    driver.setDirection(0);
  }
}
