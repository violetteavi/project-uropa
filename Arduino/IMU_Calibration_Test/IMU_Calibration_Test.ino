/*This file is for testing two brushless motor 
 *corresponding to the IMU(X-accelometer)data
 *Make sure your Arduino has Servo.h & MPU9250.h in the library
 *Arduino Uno/Lipo battery(2~3s)/power board/ESC/IMU/
 *Compile it and toyboat will run automatically
 *Case1:tilt left->run left motor powerful
 *Case2:tilt right->run right motor powerful
 *Do not use the ESC's middle pin(red) to the Arduino board
 *If you want to see the IMU data, uncomment all lines that I commented
 */
#include "Servo.h"
#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

void setup() {

  // serial to display data
  Serial.begin(9600);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);
}



void loop() {
  // read the sensor
  //while(IMU.readSensor()){}
  IMU.readSensor();
  
  float accelX = IMU.getAccelX_mss();
  float accelY = IMU.getAccelY_mss();
  float accelZ = IMU.getAccelZ_mss();
  float magX = IMU.getMagX_uT();
  float magY = IMU.getMagY_uT();
  float magZ = IMU.getMagZ_uT();

  float accelMagnitude = sqrt(accelX*accelX + accelY*accelY + accelZ*accelZ);
  float magMagnitude = sqrt(magX*magX + magY*magY + magZ*magZ);
  float dotAccelMag = accelX*magX + accelY*magY + accelZ*magZ;
  float cosTheta = dotAccelMag / accelMagnitude / magMagnitude;
  float theta = acos(cosTheta) * 180 / 3.14159;

  
  // display the data
  Serial.print("AccX: ");
  Serial.print(accelX, 4);
  Serial.print("\tAccY: ");
  Serial.print(accelY,4);
  Serial.print("\tAccZ: ");
  Serial.print(accelZ,4);
  Serial.print("\tMagX: ");
  Serial.print(magX,4);
  Serial.print("\tMagY: ");
  Serial.print(magY,4);
  Serial.print("\tMagZ: ");
  Serial.print(magZ,4);
  Serial.print("\tMgdA: ");
  Serial.print(accelMagnitude,4);
  Serial.print("\tMgdM: ");
  Serial.print(magMagnitude,4);
  Serial.print("\tCosT: ");
  Serial.print(cosTheta,4);
  Serial.print("\tThet: ");
  Serial.println(theta,4);
  delay(500);
}
