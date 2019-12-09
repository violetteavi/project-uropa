#ifndef BUOYANCY_CONTROLLER_h
#define BUOYANCY_CONTROLLER_h

#include "StepperController.h"

class BuoyancyController 
{ 
  public: 
    // 200 steps = 1 rotation
    void zero();
    void setAllToNeutral();
    void applyBuoyancy(long steps);
    void applyRoll(long steps);
    void applyPitch(long steps);
    
    bool updatePulseApplication();
    bool calibrate();
    BuoyancyController(StepperController* frontLeftController,
                        StepperController* backLeftController,
                        StepperController* frontRightController,
                        StepperController* backRightController);
    
  private:
    StepperController* frontLeft;
    StepperController* backLeft;
    StepperController* frontRight;
    StepperController* backRight;

    const long TRAVEL_LENGTH_STEPS = 50000L;
}; 

#endif
