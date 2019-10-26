

/*This is the file for testing the motors with the turning data from the pixy-CDR
1. Make sure the arduino device name is right one ex) /dev/ttyACM1 or '/dev/ttyACM0'
-> change it in the get_blocks.py 
2. Due to IMU sensor library file issue, we are not using the code related to the sensor
-> All the codes are commented
*/
#include "Servo.h"
//#include "Wire.h"
//#include "SPI.h"
//#include "MPU9250.h"
#include <ESC.h>
#define SPEED_MIN (1100)
#define SPEED_MAX (1500)
#define PROPORTION_CAP (1)
//MPU9250 IMU(Wire,0x68);
int status;
ESC myESCL (11, SPEED_MIN, SPEED_MAX, 500);//Left side motor
ESC myESCR (12, SPEED_MIN, SPEED_MAX, 500);//Right side motor

//int leftMotorPin = 11;
//int rightMotorPin = 12;
int enablePin = 2;
int ledPin = 5;
int watchdogPeriod = 1000;
int lastUpdateTime;

//int minSpeed = 55;
//int maxSpeed = 80;

void setup() {
  Serial.begin(9600);
  myESCL.arm();//Left side ESC signal pin10
  myESCR.arm();//Right side ESC signal pin9
 
  while(!Serial) {}
  //status = IMU.begin();
  // setting the accelerometer full scale range to +/-8G 
  //IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  //IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  //IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  //IMU.setSrd(19);

  //Serial.println("Ready");
  pinMode(enablePin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  //delay(5000);
  enableMotors(false);
  lastUpdateTime = millis();
}

void loop(){
  if(digitalRead(enablePin) == LOW)
  {
    enableMotors(false);
    return;
  }
  float f;
  if(Serial.available()){
   
   // f is the variable that receives the turning values from pixy 
   int transferInt = Serial.parseInt();
   if(transferInt < 0  || transferInt >= 10000) return;
   int leftMotorInt = (transferInt / 100);
   int rightMotorInt = transferInt % 100;
   Serial.print("TransferInt:\t");
   Serial.print(transferInt);
   Serial.print("\tLeftMotorInt:\t");
   Serial.print(leftMotorInt);
   Serial.print("\tRightMotorInt:\t");
   Serial.print(rightMotorInt);
   Serial.println();
   float leftMotorFloat = leftMotorInt / 100.0 * PROPORTION_CAP;
   float rightMotorFloat = rightMotorInt / 100.0 * PROPORTION_CAP;
   
   int leftMotorSignal = (int)(leftMotorFloat * (SPEED_MAX- SPEED_MIN) + SPEED_MIN);
   int rightMotorSignal = (int)(rightMotorFloat * (SPEED_MAX- SPEED_MIN) + SPEED_MIN);
   /*
   Serial.print("LeftMotor:\t");
   Serial.print(leftMotorSignal);
   Serial.print("\tRightMotor:\t");
   Serial.print(rightMotorSignal);
   Serial.println();
   */
   //Serial.println("\t");
   //Serial.println(IMU.getAccelX_mss());
   /*
   myESCL.speed(leftMotorSignal); 
   myESCR.speed(rightMotorSignal); 
   delay(10);
   digitalWrite(ledPin, HIGH);
   */
   enableMotors(false);
   
   lastUpdateTime = millis();
 
  //Case:1
        // if (IMU.getAccelX_mss()<=-1.5){
        //    ESCL.write(90); 
       //     }
  //Case:2enableMotors
         //else if (IMU.getAccelX_mss()>=1){
        //    ESCR.write(90);
         //    }
  
  }
  //If the data is not received turn the motors off
  else
    if(millis() - lastUpdateTime > watchdogPeriod)
    {
      enableMotors(false);
    }
  }
  
  
void enableMotors(bool active)
{
  if(active)
  {
      myESCL.speed(SPEED_MAX); // COMMENT THIS OUT TO TURN LEFT    (BOTH UNCOMMENTED IS FULL FWD)
      myESCR.speed(SPEED_MAX); // COMMENT THIS OUT TO TURN RIGHT
      digitalWrite(ledPin, HIGH);
      delay(10);
  }
  else
  {
      myESCL.speed(SPEED_MIN);
      myESCR.speed(SPEED_MIN);
      digitalWrite(ledPin, LOW);
      delay(10);
  }
}
  
