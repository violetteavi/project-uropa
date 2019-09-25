
void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop(){
  float f;
  if(Serial.available()){
     
   f = Serial.parseFloat();
   Serial.println(f);
  }
  
}
