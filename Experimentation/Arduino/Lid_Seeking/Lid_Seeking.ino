#include "Servo.h"
<<<<<<< HEAD:UART_talk/UART_talk.ino
#include "MPU9250.h"

MPU9250 IMU(Wire,0x68);
=======
//#include "MPU9250.h"

//MPU9250 IMU(Wire,0x68);
>>>>>>> master:Arduino/Lid_Seeking/Lid_Seeking.ino
int status;
Servo ESCL;//Left side motor
Servo ESCR;//Right side motor

void setup() {
  Serial.begin(9600);
 ESCL.attach(10);//Left side ESC signal pin10
 ESCR.attach(9);//Right side ESC signal pin9
  while(!Serial) {}
<<<<<<< HEAD:UART_talk/UART_talk.ino
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
  // delay(500);
  
  /// ESCL.write(60);
  // ESCR.write(60);
  // delay(2000);

  // ESCL.write(0);
  // ESCL.write(0);
  
=======
 // status = IMU.begin();
  // setting the accelerometer full scale range to +/-8G 
 // IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
 // IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
 // IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
 // IMU.setSrd(19);
//Initializing two motor power as 0 at the beginning  
  ESCL.write(0);
  ESCR.write(0);
>>>>>>> master:Arduino/Lid_Seeking/Lid_Seeking.ino
  Serial.println("Ready");
}

void loop(){
  float f;
<<<<<<< HEAD:UART_talk/UART_talk.ino
  if(Serial.available() || IMU.readSensor() ){
     
   //f = Serial.parseFloat();
=======
  if(Serial.available()){
     
   f = Serial.parseFloat();
>>>>>>> master:Arduino/Lid_Seeking/Lid_Seeking.ino

    Serial.print("Camera Turning");
     Serial.print("\t");
     Serial.println("AccelX");
     Serial.print(f);
     Serial.print("\t");
<<<<<<< HEAD:UART_talk/UART_talk.ino
     Serial.println(IMU.getAccelX_mss());
=======
//     Serial.println(IMU.getAccelX_mss());
>>>>>>> master:Arduino/Lid_Seeking/Lid_Seeking.ino
        if(f>=0){
     ESCL.write(55);
     ESCR.write(55);
        }
  //Case:1
<<<<<<< HEAD:UART_talk/UART_talk.ino
         if (IMU.getAccelX_mss()<=-1.5){
            ESCL.write(100); 
            }
  //Case:2
         else if (IMU.getAccelX_mss()>=1){
                 ESCR.write(100);
             }

             
  delay(500);

  
  }
  }
  
=======
   //      if (IMU.getAccelX_mss()<=-1.5){
   //         ESCL.write(90); 
   //         }
  //Case:2
   //      else if (IMU.getAccelX_mss()>=1){
   //              ESCR.write(90);
   //          }
  delay(500);
  }
  }
>>>>>>> master:Arduino/Lid_Seeking/Lid_Seeking.ino
