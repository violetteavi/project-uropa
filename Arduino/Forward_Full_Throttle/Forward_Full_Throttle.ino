#include "Servo.h"
//#include "MPU9250.h"
#include <ESC.h>
#define SPEED_MIN (1000)
#define SPEED_MAX (2000)
//MPU9250 IMU(Wire,0x68);

//int leftMotorPin = 11;
//int rightMotorPin = 12;
int enablePin = 2;
int ledPin = 5;
double powerProportion = 0.4;
int status;

//MPU9250 IMU(Wire,0x68);

ESC myESCL (12, SPEED_MIN, SPEED_MAX, 500);//Left side motor
ESC myESCR (11, SPEED_MIN, SPEED_MAX, 500);//Right side motor
//int maxSpeed = 90;
int period = 10000;
bool isActive = false;
bool enabled = false;
int startTime;
  
void setup() {
  //Serial.begin(9600);
  myESCL.arm();//Left side ESC signal pin10
  myESCR.arm();//Right side ESC signal pin9
  
  //Serial.println("Ready");
  pinMode(enablePin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  startTime = millis();
  delay(5000);

}

void loop(){
  myESCL.arm();//Left side ESC signal pin10
  myESCR.arm();//Right side ESC signal pin9
  bool prevEnabled = enabled;
  enabled = (digitalRead(enablePin) == HIGH); //
  if(enabled and !prevEnabled)
  {
      isActive = true;
      startTime = millis();
  }
  
  if(enabled)
  {
    enableMotors(isActive);
    int deltaTime = millis() - startTime;
    if(deltaTime > period)
    {
      isActive = !isActive;
      startTime = millis();
    }
  }
  else
  {
      isActive = false;
      enableMotors(false);
  }
}

void enableMotors(bool active)
{
  if(active)
  {
      int motorPower = (int)(powerProportion*(SPEED_MAX-SPEED_MIN) + SPEED_MIN);
      myESCL.speed(motorPower); // COMMENT THIS OUT TO TURN LEFT    (BOTH UNCOMMENTED IS FULL FWD)
      myESCR.speed(motorPower); // COMMENT THIS OUT TO TURN RIGHT
      delay(100);
      digitalWrite(ledPin, HIGH);
  }
  else
  {
      //ESCL.write(55);
      myESCL.speed(SPEED_MIN);
      myESCR.speed(SPEED_MIN);
      delay(100);
      digitalWrite(ledPin, LOW);
  }
}
