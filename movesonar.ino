const int distance = 3;
long pulse, cm;

void setup() {
pinMode(distance,INPUT);
Serial.begin(9600);// put your setup code here, to run once:

}

void loop() {

  pulse = pulseIn(distance, HIGH);

  //58uS per cm

  cm = pulse *2.54/120;
//37cm
  Serial.print(cm);

  Serial.print("cm");

  Serial.println();

  delay(500);

   }
