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
    StepperController(uint8_t CSPin, int bottomSwitchPin, int topSwitchPin);
  private:
    HighPowerStepperDriver driver;
    const int DEAD_ZONE = 0;
    const int TRAVEL_LENGTH_STEPS = 10000;
    void setDirectionIfNecessary(bool forward);

    private int chipSelect;
    private int bottomSwitch;
    private int topSwitch
}; 

#endif
