#ifndef STEPPER_CONTROLLER_h
#define STEPPER_CONTROLLER_h

#include <SPI.h>
#include <HighPowerStepperDriver.h>

class StepperController 
{ 
  public: 
    float targetStepCount = 0;
    float currentStepCount = 0;
    
    bool updatePulseApplication(); 
    StepperController(uint8_t CSPin);
  private:
    HighPowerStepperDriver driver;
    const int DEAD_ZONE = 0;
    void setDirectionIfNecessary(bool forward);
}; 

#endif
