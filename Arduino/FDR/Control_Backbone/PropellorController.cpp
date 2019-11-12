#include "PropellorController.h"

PropellerController::PropellerController(int drivePin)
{
  ESC* controller = new ESC(drivePin, PWM_MAXB, PWM_MAXF, PWM_STOP);
  lastUpdateMillis = -1;
}

bool PropellerController::updateVelocity()
{
  float setpoint = max(0, min(1, targetProportion));
  if(setpoint == currentProportion) 
  {
    lastUpdateMillis = -1;
    return false;
  }
  float slowedSetpoint = calculateSlowedSetpoint(setpoint, currentProportion);
  int pwmSetpoint = proportionToPWM(slowedSetpoint);
  controller->speed(pwmSetpoint);
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
      setpoint = current + allowableDifference;
    }
    if(setpointDifference < 0)
    {
      setpoint = current - allowableDifference;
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
  proportion = max(0, min(1, proportion));
  if(proportion > 0)
  {
    int pwmF = (int)(proportion*(PWM_MAXF-PWM_MINF) + PWM_MINF);
    return pwmF;
  }
  else if(proportion < 0)
  {
    proportion *= -1;
    int pwmB = (int)(proportion*(PWM_MAXB-PWM_MINB) + PWM_MINB);
    return pwmB;
  }
  else
  {
    return PWM_STOP;
  }
}
