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

//MPU9250 IMU(Wire,0x68);
int status;
Servo ESCL;//Left side motor
Servo ESCR;//Right side motor

int ledPin = 5;

void setup() {
  Serial.begin(9600);
  ESCR.attach(11);//Right side ESC signal pin9
  ESCL.attach(12);//Left side ESC signal pin10
 
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
//Initializing two motor power as 0 at the beginning  
  ESCL.write(0);
  ESCR.write(0);

  //Serial.println("Ready");
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
}

void loop(){
  float f;
  if(Serial.available()){
   
   // f is the variable that receives the turning values from pixy 
   f = Serial.parseFloat();

   //Serial.print  ("Camera Turning");
   //Serial.println("\t");
   //Serial.println("AccelX");
  // Serial.print(f);
   //Serial.println("\t");
   //Serial.println(IMU.getAccelX_mss());
   if(f>0){
    enableMotors(true);
   }
   //The data received negative value = The target is not in the area of the camera 
   else if(f<0){
    enableMotors(false);
    
   }
 
  //Case:1
        // if (IMU.getAccelX_mss()<=-1.5){
        //    ESCL.write(90); 
       //     }
  //Case:2
         //else if (IMU.getAccelX_mss()>=1){
        //    ESCR.write(90);
         //    }
  
  }
  //If the data is not received turn the motors off
  else
    enableMotors(false);
  
  }
  
  
void enableMotors(bool active)
{
  if(active)
  {
      ESCL.write(179); // COMMENT THIS OUT TO TURN LEFT    (BOTH UNCOMMENTED IS FULL FWD)
      ESCR.write(179); // COMMENT THIS OUT TO TURN RIGHT
      digitalWrite(ledPin, HIGH);
  }
  else
  {
      ESCL.write(55);
      ESCR.write(55);
      digitalWrite(ledPin, LOW);
  }
}
  
