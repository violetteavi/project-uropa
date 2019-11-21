#include "AccelerometerReader.h"


AccelerometerReader::AccelerometerReader(uint8_t address)
{
  IMU = new MPU9250(Wire, address);
  int status = IMU->begin();
  if (status < 0) {
    errorFlag = true;
    return;
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU->setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU->setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU->setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU->setSrd(19);
}

bool AccelerometerReader::updateAccelerometerVals()
{
  return false;
}

