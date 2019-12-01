#include "PropellerController.h"

PropellerController::PropellerController(int drivePin)
{
  controller = new ESC(18, PWM_MAXB, PWM_MAXF, 500);
  controller->arm();
  delay(1000);
  targetProportion = 1;
  while(updateVelocity())
  {
    delay(10);
  }
  delay(1000);
  targetProportion = -1;
  while(updateVelocity())
  {
    delay(10);
  }
  delay(1000);
  targetProportion = 0;
  while(updateVelocity())
  {
    delay(10);
  }
  lastUpdateMillis = -1;
  
}

bool PropellerController::updateVelocity()
{
  float setpoint = max(-1, min(1, targetProportion));
  if(setpoint == currentProportion) 
  {
    lastUpdateMillis = -1;
    return false;
  }
  float slowedSetpoint = calculateSlowedSetpoint(setpoint, currentProportion);
  int pwmSetpoint = proportionToPWM(slowedSetpoint);
  controller->speed(pwmSetpoint);
  currentProportion = slowedSetpoint;
  lastUpdateMillis = millis();
  return true;
}

float PropellerController::calculateSlowedSetpoint(float setpoint, float current)
{
  float setpointDifference = setpoint - current;
  float slowedSetpoint = setpoint;
  float allowableDifference = maxAllowablePropDifference(lastUpdateMillis);
  if(abs(setpointDifference) > allowableDifference)
  {
    if(setpointDifference > 0)
    {
      slowedSetpoint = current + allowableDifference;
    }
    if(setpointDifference < 0)
    {
      slowedSetpoint = current - allowableDifference;
    }
  }
  return slowedSetpoint;
}

float PropellerController::maxAllowablePropDifference(int lastMillis)
{
  if(lastMillis == -1)
  {
    return MAX_STEP_JUMP;
  }

  int deltaTime = millis() - lastMillis;
  float propDifference = deltaTime * MAX_ACCEL_PER_MS;
  propDifference = min(MAX_STEP_JUMP, propDifference);
  return propDifference;
}

int PropellerController::proportionToPWM(float proportion)
{
  proportion = max(-1, min(1, proportion));
  if(proportion > 0)
  {
    int pwmF = (int)(proportion*(PWM_MAXF-PWM_STOP) + PWM_STOP);
    return pwmF;
  }
  else if(proportion < 0)
  {
    proportion *= -1;
    int pwmB = (int)(proportion*(PWM_MAXB-PWM_STOP) + PWM_STOP);
    return pwmB;
  }
  else
  {
    return PWM_STOP;
  }
}
