#ifndef STEPPER_CONTROLLER_h
#define STEPPER_CONTROLLER_h

#include <SPI.h>
#include <HighPowerStepperDriver.h>

class StepperController 
{ 
  public: 
    long targetStepCount = 0;
    long currentStepCount = 0;
    
    bool updatePulseApplication(); 
    StepperController(uint8_t CSPin, int bottomSwitchPin, int topSwitchPin);
  private:
    HighPowerStepperDriver driver;
    const long DEAD_ZONE = 0;
    void setDirectionIfNecessary(bool forward);

    int chipSelect;
    int bottomSwitch;
    int topSwitch;
}; 

#endif
