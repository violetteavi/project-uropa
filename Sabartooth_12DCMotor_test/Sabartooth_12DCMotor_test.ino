/*ME463 UROPA - made by HYUKJUN JANG
 * This code is for testing power of motors giving different Duty(0~255) 
 * Average Voltage = (Duty ÷ 256) x 5 volts
 * Sabartooth 2x32 / ArduinoMega/two 12V DC Motors/12V battery
 */
const int Motor1 = 2;//for the motor attached to M1A,M1B(motordrive)//ArduinoMega(pin2)
const int Motor2 = 4;//for the motor attached to M2A,M2B//ArduinoMega(pin3)

void setup() {

pinMode(Motor1, OUTPUT);
pinMode(Motor2, OUTPUT);
Serial.begin(9600);
Serial.println("Enter values between 0- 255");

}

void loop() {

/*Available to see the power by putting Duty value on the serial monitor  
 *Change the code to analogWrite(Motor2,speed) if you want to test Motor2
 */
  if(Serial.available())
  {
    int speed = Serial.parseInt(); //Receive Value from serial monitor
    Serial.println(speed);
      analogWrite(Motor1,speed);
  }


}
