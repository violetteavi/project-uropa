/*ME463 UROPA - made by HYUKJUN JANG
 * This code is for testing power of motors giving different Duty(0~255) 
 * Average Voltage = (Duty ÷ 256) x 5 volts
 * Modified--> 
 * 1.Motors will be operated by a laptop keyboard input(a,s,d,w)
 * 2.Before compiling, Click Tools tab and make sure Board(Mega2560) and Port should be defined
 * 3.Make sure set 9600 baud rate on Serial monitor(located at down rigt) 
 */


const int Motor1L =8;//IN1 pin 8
const int Motor1R =9;//IN2 pin 9
const int enA = 2;//for the motor attached to M1A,M1B(motordrive)//ArduinoMega(pin2)
const int Motor2L = 4;//for the motor attached to M2A,M2B//ArduinoMega(pin4)
const int Motor2R = 5; // pin 5
const int enB = 6; // pin 6
char val =0;

void setup() {

pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
//Motor1 label is for a main motor
pinMode(Motor1L, OUTPUT);
pinMode(Motor1R, OUTPUT);
//Motor2 label is for side motors
pinMode(Motor2L, OUTPUT);
pinMode(Motor2R, OUTPUT);

Serial.begin(9600);
Serial.println("Enter the key command(a,d,s,w)");

}

void loop() {
 
   
/*Available to see the power by putting Duty value on the serial monitor  

/*Modified->
 * 1. If you want to change the power of the motor,you should 
 * manually edit the number(0~255)below and compile it)
 * 2. If you want to run it longer, edit the delay()[unit:ms]
  */
  if(Serial.available())
  {
    //int speed = Serial.parseInt(); //Receive Value from serial monitor
    val = Serial.read();
    //Set Motors speed maximum range 255
    analogWrite(enA, 255);
    analogWrite(enB, 255);
   

//if the value input is equal to s, main motor runs to make it go backward
    if (val== 's'){
      //Run the left&right motors to go backward
      analogWrite(Motor1L,0);
      analogWrite(Motor1R,255);
      analogWrite(Motor2L,255);
      analogWrite(Motor2R,0);
      Serial.println("Backward");
      delay(3000);
    }
//if the value input is equal to a, side motor runs to make it turn left
    else if(val == 'a'){
      
      analogWrite(Motor1L,255);
      analogWrite(Motor1R,0);
      
      analogWrite(Motor2L,255);
      analogWrite(Motor2R,0);
       Serial.println("Left");
      delay(3000);

    }
//if the value input is equal to w,both motors run to make it go foward
    else if(val =='w'){
      analogWrite(Motor1L,255);
      analogWrite(Motor1R,0);
      analogWrite(Motor2L,0);
      analogWrite(Motor2R,255);
      Serial.println("FORWARD");
      delay(3000);
    }
//if the value input is equal to d,both motors run to make it turn right
    else if(val =='d'){
      
      analogWrite(Motor1L,0);
      analogWrite(Motor1R,255);
      
      analogWrite(Motor2L,0);
      analogWrite(Motor2R,255);
      Serial.println("Right");
      delay(3000);
    }
   
    else
      analogWrite(Motor1L,0);
      analogWrite(Motor1R,0);
      analogWrite(Motor2R,0);
      analogWrite(Motor2L,0);
    }


}
