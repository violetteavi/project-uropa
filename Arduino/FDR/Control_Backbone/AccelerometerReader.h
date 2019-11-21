#ifndef ACCELEROMETER_READER_h
#define ACCELEROMETER_READER_h

#include <Wire.h>
#include <MPU9250.h>

class AccelerometerReader 
{ 
  public: 
    // pitch angle phi radians, defined as positive x (right from top view)
    float pitchAngle = 0;
    // roll angle theta radians, defined as positive z (into cave)
    float rollAngle = 0;
    // down acceleration, defined as positive y (down)
    float downAcceleration = 9.8;
    
    bool updateAccelerometerVals();
    AccelerometerReader(uint8_t address=0x68);
    ~AccelerometerReader();
    
    bool errorFlag = false;
  private:
    // an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
    MPU9250* IMU;
    bool updatePitchAngle(float accelZ);
    bool updateRollAngle(float accelX);

    float gravity = 9.8;
}; 

#endif
