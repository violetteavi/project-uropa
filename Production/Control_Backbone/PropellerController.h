#ifndef PROPELLER_CONTROLLER_h
#define PROPELLER_CONTROLLER_h

#include "ESC.h"

class PropellerController 
{ 
  public: 
    // Proportions are in range -1 to 1
    float targetProportion = 0;
    float currentProportion = 0;
    
    bool updateVelocity();
    PropellerController(int drivePin);
    
    const int PWM_MAXB = 1100; //backward max 
    const int PWM_MINB = 1460; //backward min 
    const int PWM_STOP = 1500; //Stop
    const int PWM_MINF = 1530; //forward min 
    const int PWM_MAXF = 1900; //forward max 

    // This is conservative: stop to full in 1 sec, minimum
    const float MAX_ACCEL_PER_MS = 0.001;
    const float MAX_STEP_JUMP = 0.01;
  private:
    ESC* controller;
    int lastUpdateMillis = -1;
    
    float calculateSlowedSetpoint(float setpoint, float current);
    float maxAllowablePropDifference(int lastMillis);
    int proportionToPWM(float proportion);
}; 

#endif
