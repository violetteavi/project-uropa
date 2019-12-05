#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include "MPU9250.h"
const uint8_t CSPin4 = 12;
const uint8_t CSPin3 = 11;
const uint8_t CSPin2 = 10;
const uint8_t CSPin = 9;
MPU9250 IMU(Wire,0x68);
int status;
// This period is the length of the delay between steps, which controls the
// stepper motor's speed.  You can increase the delay to make the stepper motor
// go slower.  If you decrease the delay, the stepper motor will go faster, but
// there is a limit to how fast it can go before it starts missing steps.
const uint16_t StepPeriodUs = 2000;

HighPowerStepperDriver sd;
HighPowerStepperDriver sd2;
HighPowerStepperDriver sd3;
HighPowerStepperDriver sd4;
void setup()
{
  SPI.begin();
  sd.setChipSelectPin(CSPin);
  sd2.setChipSelectPin(CSPin2);
  sd3.setChipSelectPin(CSPin3);
  sd4.setChipSelectPin(CSPin4);
  //sd.setChipSelectPin(CSPin1);
  // Give the driver some time to power up.
  delay(2);

  // Reset the driver to its default settings and clear latched status
  // conditions.
  sd.resetSettings();
  sd.clearStatus();
  sd2.resetSettings();
  sd2.clearStatus();
  sd3.resetSettings();
  sd3.clearStatus();
  sd4.resetSettings();
  sd4.clearStatus();
  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  // for most applications, and we find that it usually works well.
  //sd.setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  sd.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max
  sd2.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max
  sd3.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max
  sd4.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max
  // Set the number of microsteps that correspond to one full step.
  sd.setStepMode(HPSDStepMode::MicroStep1);
  sd2.setStepMode(HPSDStepMode::MicroStep1);
  sd3.setStepMode(HPSDStepMode::MicroStep1);
  sd4.setStepMode(HPSDStepMode::MicroStep1);
  // Enable the motor outputs.
  sd.enableDriver();
  sd2.enableDriver();
  sd3.enableDriver();
  sd4.enableDriver();
  //pinMode(49, OUTPUT);
  //digitalWrite(49, HIGH);
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

void loop()
{
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

  // Step in the default direction 1000 times.
  //sd.setDirection(0);//cc
  //sd2.setDirection(0);//cc
  sd3.setDirection(0);//cc
  //sd4.setDirection(0);//cc
  //delayMicroseconds(100);
  for(unsigned int x = 0; x < 1000; x++)
  {
    //sd.step();
    //sd2.step();
    sd3.step();
    //sd4.step();
    delayMicroseconds(StepPeriodUs);
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

  // Wait for 300 ms.
  //delay(3000);

  // Step in the other direction 1000 times.
  //sd.setDirection(1);//clc
  //sd2.setDirection(1);//clc
  sd3.setDirection(1);//clc
  //sd4.setDirection(1);//clc
  //delayMicroseconds(100);
  for(unsigned int x = 0; x < 1000; x++)
  {
    //sd.step();
    //sd2.step();
    sd3.step();
    //sd4.step();
    delayMicroseconds(StepPeriodUs);
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

  // Wait for 300 ms.
  //delay(5000);
}
