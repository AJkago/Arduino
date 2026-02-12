int solenoid = 13;
int tempo = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoid,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int k=0;k<3;k++){
    for(int i=0;i<3;i++){
      digitalWrite(solenoid,HIGH);
      delay(tempo);
      digitalWrite(solenoid,LOW);
      delay(tempo); 
    }
    delay(tempo*3);
  }

  digitalWrite(solenoid,HIGH);
  delay(tempo);
  digitalWrite(solenoid,LOW);
  delay(tempo);

  delay(tempo*9);
}
