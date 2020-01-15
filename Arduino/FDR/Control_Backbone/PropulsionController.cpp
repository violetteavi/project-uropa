#include "PropulsionController.h"

PropulsionController::PropulsionController(PropellerController* leftPropController, PropellerController* rightPropController)
{
  leftProp = leftPropController;
  rightProp = rightPropController;
  leftProp->targetProportion = 0;
  rightProp->targetProportion = 0;
}

bool PropulsionController::updatePropulsion()
{
  Serial.println("Not written!");
}
