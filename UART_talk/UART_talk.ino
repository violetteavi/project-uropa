#include "Servo.h"
#include "MPU9250.h"

MPU9250 IMU(Wire,0x68);
int status;
Servo ESCL;//Left side motor
Servo ESCR;//Right side motor

void setup() {
  Serial.begin(9600);
 ESCL.attach(10);//Left side ESC signal pin10
 ESCR.attach(9);//Right side ESC signal pin9
  while(!Serial) {}
  status = IMU.begin();
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
  Serial.println("Ready");
}

void loop(){
  float f;
  if(Serial.available() && IMU.readSensor() ){
     
   f = Serial.parseFloat();

    Serial.print("Camera Turning");
     Serial.print("\t");
     Serial.println("AccelX");
     Serial.print(f);
     Serial.print("\t");
     Serial.println(IMU.getAccelX_mss());
        if(f>=0){
     ESCL.write(55);
     ESCR.write(55);
        }
  //Case:1
         if (IMU.getAccelX_mss()<=-1.5){
            ESCL.write(90); 
            }
  //Case:2
         else if (IMU.getAccelX_mss()>=1){
                 ESCR.write(90);
             }
  delay(500);
  }
  }
  
