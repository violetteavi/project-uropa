/*This file is to test a watersensor with LED&330ohm
 * + -->5V
 * - -->GND
 * S -->Pin52
 * 330 ohm to GND of LED
 */
#define Grove_Water_Sensor 52 // Attach Water sensor to Arduino Digital Pin 52
#define LED 53 // Attach an LED to Digital Pin 53

void setup() {
   pinMode(Grove_Water_Sensor, INPUT); // The Water Sensor is an Input
   pinMode(LED, OUTPUT); // The LED is an Output
}

void loop() {
   /* The water sensor will switch HIGH when water is detected.
   Get the Arduino to illuminate the LED when water is detected, and switch it off when no water is present */
   if( digitalRead(Grove_Water_Sensor) == HIGH) {
      digitalWrite(LED,HIGH);
      
   }else {
      digitalWrite(LED,LOW);
   }
}
