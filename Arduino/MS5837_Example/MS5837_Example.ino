/* Blue Robotics MS5837 Library Example
-----------------------------------------------------
 
Title: Blue Robotics MS5837 Library Example

Description: This example demonstrates the MS5837 Library with a connected
sensor. The example reads the sensor and prints the resulting values
to the serial terminal.

The code is designed for the Arduino Uno board and can be compiled and 
uploaded via the Arduino 1.0+ software.

-------------------------------
The MIT License (MIT)

Copyright (c) 2015 Blue Robotics Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/

#include <Wire.h>
#include "MS5837.h"
#include "Servo.h"
#include "MPU9250.h"
// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
MS5837 sensor;

void setup() {
  
  Serial.begin(9600);
  while(!Serial) {}
  Serial.println("Starting");
  
  Wire.begin();
  status = IMU.begin();
  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
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

  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }
  
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
}

void loop() {
  // Update pressure and temperature readings
  sensor.read();
  IMU.readSensor();
  Serial.print("Pressure: "); 
  Serial.print(sensor.pressure()); 
  Serial.println(" mbar");
  
  Serial.print("Temp erature: "); 
  Serial.print(sensor.temperature()); 
  Serial.println(" deg C");
  
  Serial.print("Depth: "); 
  Serial.print(sensor.depth()); 
  Serial.println(" m");
  
  Serial.print("Altitude: "); 
  Serial.print(sensor.altitude()); 
  Serial.println(" m above mean sea level");
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
  //delay(500);
  delay(1000);
}
