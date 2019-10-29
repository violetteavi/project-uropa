

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
#define MAX_BUFF_LENGTH (50)
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
int bufferReadFlag = 0;
char serialBuffer1[MAX_BUFF_LENGTH];
int buffer1Length = 0;
char serialBuffer2[MAX_BUFF_LENGTH];
int buffer2Length = 0;
int writeBuffer = 1;
int transferInt = 0;

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
  parseTransferInt();
  if(digitalRead(enablePin) == LOW)
  {
    enableMotors(false);
    return;
  }
  
  if(millis() - lastUpdateTime < watchdogPeriod)
  { 
   if(transferInt < 0  || transferInt >= 10000) return;
   int leftMotorInt = (transferInt / 100);
   int rightMotorInt = transferInt % 100;
   float leftMotorFloat = leftMotorInt / 100.0 * PROPORTION_CAP;
   float rightMotorFloat = rightMotorInt / 100.0 * PROPORTION_CAP;
   
   int leftMotorSignal = (int)(leftMotorFloat * (SPEED_MAX- SPEED_MIN) + SPEED_MIN);
   int rightMotorSignal = (int)(rightMotorFloat * (SPEED_MAX- SPEED_MIN) + SPEED_MIN);
   myESCL.speed(leftMotorSignal); 
   myESCR.speed(rightMotorSignal); 
   delay(10);
   digitalWrite(ledPin, HIGH);
   //*/
   //enableMotors(false);
   /*
   Serial.print("LeftMotor:\t");
   Serial.print(leftMotorSignal);
   Serial.print("\tRightMotor:\t");
   Serial.print(rightMotorSignal);
   Serial.println();
   */
   //Serial.println("\t");
   //Serial.println(IMU.getAccelX_mss());
   ///*
 
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
  {
    enableMotors(false);
  }
}

void parseTransferInt()
{
  int potentialTransferInt = -1;
  switch(bufferReadFlag)
  {
    case 0: 
      return; // no packet fully written yet
    case 1: 
      potentialTransferInt = atoi(serialBuffer1);
      break;
    case 2:
      potentialTransferInt = atoi(serialBuffer2);
      break;
  }
  if(potentialTransferInt >= 0  && potentialTransferInt < 10000)
  {
    transferInt = potentialTransferInt;
    lastUpdateTime = millis();
    bufferReadFlag = 0;
    //Serial.print("TransferInt:\t");
    //Serial.println(transferInt);
  }
}

void serialEvent()
{
  int readByte;
  while((readByte = Serial.read()) != -1)
  {
    char readChar = readByte;
    serialByteRecieved(readChar);
    //Serial.print(readChar);
  }
}

void serialByteRecieved(char byteRecieved)
{
  char byteToWrite = byteRecieved;
  if(byteRecieved == '\n') byteToWrite = '\0';
  switch(writeBuffer)
  {
    case 1:
      serialBuffer1[buffer1Length] = byteToWrite;
      buffer1Length++;
      buffer1Length = min(buffer1Length, MAX_BUFF_LENGTH - 1);
    case 2:
      serialBuffer2[buffer2Length] = byteToWrite;
      buffer2Length++;
      buffer2Length = min(buffer2Length, MAX_BUFF_LENGTH - 1);
  }
  
  if(byteRecieved == '\n')
  {
    // end of packet, set read flag
    // then switch buffers
    bufferReadFlag = writeBuffer;
    switch(writeBuffer)
    {
      case 1: 
        buffer1Length = 0;
        writeBuffer = 2;
        break;
      case 2: 
        buffer2Length = 0;
        writeBuffer = 1;
        break;
    }
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
  
