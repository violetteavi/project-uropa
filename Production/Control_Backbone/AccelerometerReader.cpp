#include "AccelerometerReader.h"

AccelerometerReader::AccelerometerReader(TwoWire &bus, uint8_t busAddress)
{
  IMU = new MPU9250(bus, busAddress);
  errorStatus = IMU->begin();
  if (errorStatus >= 0) {
    // setting the accelerometer full scale range to +/-8G 
    IMU->setAccelRange(MPU9250::ACCEL_RANGE_8G);
    // setting the gyroscope full scale range to +/-500 deg/s
    IMU->setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    // setting DLPF bandwidth to 20 Hz
    IMU->setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
    // setting SRD to 19 for a 50 Hz update rate
    IMU->setSrd(19);
  }
}
AccelerometerReader::~AccelerometerReader() {  delete IMU; }

bool AccelerometerReader::updateAccelerometerVals()
{
  //noInterrupts();
  errorStatus = IMU->readSensor();
  //interrupts();
  if (errorStatus < 0) {
    return false;
  }

  float accelXRobot = IMU->getAccelX_mss();
  float accelYRobot = IMU->getAccelZ_mss();
  float accelZRobot = IMU->getAccelY_mss();

  bool successfulPitch = updatePitchAngle(accelZRobot);
  bool successfulRoll = updateRollAngle(accelXRobot);
  downAcceleration = accelYRobot;

  if(successfulPitch && successfulRoll) errorStatus = 0;
  return successfulPitch && successfulRoll;
}

bool AccelerometerReader::updatePitchAngle(float accelZ)
{
  float nonDimZ = accelZ/gravity;
  if(nonDimZ < - 1 || 1 < nonDimZ)
  {
    errorStatus = -100;
    return false;
  }
  pitchAngle = asin(nonDimZ);
  return true;
}

bool AccelerometerReader::updateRollAngle(float accelX)
{
  float nonDimX = accelX/gravity;
  if(nonDimX < - 1 || 1 < nonDimX)
  {
    errorStatus = -200;
    return false;
  }
  rollAngle = asin(nonDimX);
  return true;
}
