#include "BuoyancyController.h"


// 200 steps = 1 rotation     
BuoyancyController::BuoyancyController(StepperController* frontLeftController,
                        StepperController* backLeftController,
                        StepperController* frontRightController,
                        StepperController* backRightController)
{
  frontLeft = frontLeftController;
  backLeft = backLeftController;
  frontRight = frontRightController;
  backRight = backRightController;
}


bool BuoyancyController::updatePulseApplication()
{
  bool stepped = false;
  stepped = stepped || frontLeft->updatePulseApplication();
  stepped = stepped || backLeft->updatePulseApplication();
  stepped = stepped || frontRight->updatePulseApplication();
  stepped = stepped || backRight->updatePulseApplication();
  return stepped;
}

bool BuoyancyController::calibrate()
{
  frontLeft->targetStepCount = -TRAVEL_LENGTH_STEPS;
  backLeft->targetStepCount = -TRAVEL_LENGTH_STEPS;
  frontRight->targetStepCount = -TRAVEL_LENGTH_STEPS;
  backRight->targetStepCount = -TRAVEL_LENGTH_STEPS;
  while(updatePulseApplication())
  {
    delayMicroseconds(1500);
  }
  zero();
  return true;
}

void BuoyancyController::zero()
{
  frontLeft->targetStepCount = 0;
  frontLeft->currentStepCount = 0;
  backLeft->targetStepCount = 0;
  backLeft->currentStepCount = 0;
  frontRight->targetStepCount = 0;
  frontRight->currentStepCount = 0;
  backRight->targetStepCount = 0;
  backRight->currentStepCount = 0;
  
}

void BuoyancyController::setAllToNeutral()
{
  frontLeft->targetStepCount = (long)(0.5*TRAVEL_LENGTH_STEPS);
  backLeft->targetStepCount = (long)(0.5*TRAVEL_LENGTH_STEPS);
  frontRight->targetStepCount = (long)(0.5*TRAVEL_LENGTH_STEPS);
  backRight->targetStepCount = (long)(0.5*TRAVEL_LENGTH_STEPS);
}

void BuoyancyController::applyBuoyancy(long steps)
{
  frontLeft->targetStepCount = frontLeft->targetStepCount + steps;
  backLeft->targetStepCount = backLeft->targetStepCount + steps;
  frontRight->targetStepCount = frontRight->targetStepCount + steps;
  backRight->targetStepCount = backRight->targetStepCount + steps;
}

void BuoyancyController::applyRoll(long steps)
{
  frontLeft->targetStepCount = frontLeft->targetStepCount + steps;
  backLeft->targetStepCount = backLeft->targetStepCount + steps;
  frontRight->targetStepCount = frontRight->targetStepCount - steps;
  backRight->targetStepCount = backRight->targetStepCount - steps;
}
void BuoyancyController::applyPitch(long steps)
{
  frontLeft->targetStepCount = frontLeft->targetStepCount + steps;
  backLeft->targetStepCount = backLeft->targetStepCount - steps;
  frontRight->targetStepCount = frontRight->targetStepCount + steps;
  backRight->targetStepCount = backRight->targetStepCount - steps;
}

