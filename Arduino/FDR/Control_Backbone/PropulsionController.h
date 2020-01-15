#ifndef PROPULSION_CONTROLLER_h
#define PROPULSION_CONTROLLER_h

#include "PropellerController.h"

class PropulsionController 
{ 
  public: 
    // Proportions are in range -1 to 1
    float targetDistance = 10; // ft
    float currentDistance = 10; // ft
    float turnProportion = 0; // from -1 to 1

    bool calibrate();
    bool updatePropulsion();
    PropulsionController(PropellerController* leftPropController, PropellerController* rightPropController);
    
  private:
    PropellerController* rightProp;
    PropellerController* leftProp;
}; 

#endif
