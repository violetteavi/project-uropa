/*ME463 UROPA - made by HYUKJUN JANG
 * This code is for testing power of motors giving different Duty(0~255) 
 * Average Voltage = (Duty ÷ 256) x 5 volts
 * Modified--> Motors will be operated by a laptop keyboard input(a,d,w)
 */
const int Motor1 = 2;//for the motor attached to M1A,M1B(motordrive)//ArduinoMega(pin2)
const int Motor2 = 4;//for the motor attached to M2A,M2B//ArduinoMega(pin3)
char val =0;
void setup() {

pinMode(Motor1, OUTPUT);//left
pinMode(Motor2, OUTPUT);//right
Serial.begin(9600);
Serial.println("Enter the key command(a,d,w)");

}

void loop() {

/*Available to see the power by putting Duty value on the serial monitor  
 *Change the code to analogWrite(Motor2,speed) if you want to test Motor2
 */
/*Modified->
 * 1. If you want to change the power of the motor,you should 
 * manually edit the number(0~255)below and compile it)
 * 2. If you want to run it longer, edit the delay()[unit:ms]
  */
  if(Serial.available())
  {
    //int speed = Serial.parseInt(); //Receive Value from serial monitor
    val = Serial.read();
    //Serial.println("Hello");

//if the value input is equal to d,left motor runs to make it turn right
    if (val== 'd'){
      analogWrite(Motor1,0);
      analogWrite(Motor2,255);
      Serial.println("LEFT");
      delay(3000);
    }
//if the value input is equal to a,right motor runs to make it turn left
    else if(val == 'a'){
      analogWrite(Motor1,255);
      analogWrite(Motor2,0);
      Serial.println("RIGHT");
      delay(3000);

    }
//if the value input is equal to w,both motors run to make it go foward
    else if(val =='w'){
      analogWrite(Motor1,255);
      analogWrite(Motor2,255);
      Serial.println("FORWARD");
      delay(3000);
    }
    else
      analogWrite(Motor1,0);
      analogWrite(Motor2,0);
    //Serial.println(speed);
    // analogWrite(Motor1,speed);
  }


}
