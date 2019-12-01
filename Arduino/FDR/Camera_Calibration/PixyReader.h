#ifndef PIXY_READER_h
#define PIXY_READER_h

#include <SPI.h>  
#include <Pixy.h>

class PixyReader 
{ 
  public: 
    float propDown = 0;
    float propAcross = 0;
    float maxBound = 0;
    int updatesSinceLastSuccess = 1000;
    // reads the bounding boxes from the pixy
    // selects the biggest, and updates the public values
    // returns success
    bool updatePixyVals(); 
    PixyReader();
  private:
    Pixy pixy;
    int getLargestBlockIndex(int blocksRead);
    void updatePixyValsBasedOnBlock(int index);

    float frameWidth = 320;
    float frameHeight = 200;
}; 

#endif
