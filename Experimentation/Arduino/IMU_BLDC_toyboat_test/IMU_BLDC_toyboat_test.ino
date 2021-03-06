<<<<<<< HEAD:IMU_BLDC_toyboat_test/IMU_BLDC_toyboat_test.ino
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
//int switchPin = 7;    // switch on pin 7

Servo ESCL;//Left side motor
Servo ESCR;//Right side motor

void setup() {
//  pinMode(switchPin, INPUT);
  // serial to display data
  Serial.begin(9600);
  ESCL.attach(10);//Left side ESC signal pin10
  ESCR.attach(11);//Right side ESC signal pin9
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
//  if (status < 0) {
//    Serial.println("IMU initialization unsuccessful");
//    Serial.println("Check IMU wiring or try cycling power");
//    Serial.print("Status: ");
//    Serial.println(status);
//    while(1) {}
//  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);

//Initializing two motor power as 0 at the beginning  
  ESCL.write(0);
  ESCR.write(0);
}



void loop() {
  // read the sensor
  //You should set more than ESCL.write(50) to run continuously
//  if(switchPin==1){
//  ESCL.write(60);
//  ESCR.write(60);
//  }
//  else
//  ESCL.write(55);
//  ESCR.write(55);
  while(IMU.readSensor()){
  
  //Case:1
    if (IMU.getAccelX_mss()<=-1.5){
    ESCL.write(90); 
  }
  //Case:2
    else if (IMU.getAccelX_mss()>=1){
    ESCR.write(90);
  }
  delay(500);
  

  
//  // display the data
  Serial.println(IMU.getAccelX_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getAccelY_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getAccelZ_mss(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroX_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroY_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getGyroZ_rads(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagX_uT(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagY_uT(),6);
//  Serial.print("\t");
//  Serial.print(IMU.getMagZ_uT(),6);
//  Serial.print("\t");
//  Serial.println(IMU.getTemperature_C(),6);
//  delay(20);
  }
}
=======
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
Servo ESCL;//Left side motor
Servo ESCR;//Right side motor

void setup() {

  // serial to display data
  Serial.begin(9600);
  ESCL.attach(10);//Left side ESC signal pin10
  ESCR.attach(9);//Right side ESC signal pin9
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

//Initializing two motor power as 0 at the beginning  
  ESCL.write(0);
  ESCR.write(0);
}



void loop() {
  // read the sensor
  //You should set more than ESCL.write(50) to run continuously
  while(IMU.readSensor()){
    ;
  //ESCL.write(90);
  //ESCR.write(90);
  //Case:1
    //if (IMU.getAccelX_mss()<=-1.5){
    //ESCL.write(150); 
  //}
  //Case:2
    //else if (IMU.getAccelX_mss()>=1){
    //ESCR.write(150);
  }
  
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
  Serial.print(accelX, 6);
  Serial.print("\tAccY: ");
  Serial.print(accelY,6);
  Serial.print("\tAccZ: ");
  Serial.print(accelZ,6);
  Serial.print("\tMagX: ");
  Serial.print(magX,6);
  Serial.print("\tMagY: ");
  Serial.print(magY,6);
  Serial.print("\tMagZ: ");
  Serial.print(magZ,6);
  Serial.print("\tMgdA: ");
  Serial.print(accelMagnitude,6);
  Serial.print("\tMgdM: ");
  Serial.print(magMagnitude,6);
  Serial.print("\tCosT: ");
  Serial.print(cosTheta,6);
  Serial.print("\tThet: ");
  Serial.println(theta,6);
  delay(500);
}
>>>>>>> master:Arduino/IMU_BLDC_toyboat_test/IMU_BLDC_toyboat_test.ino
