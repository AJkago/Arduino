  const int speakerPin=8;
  const int sensorPin=A0;
  
void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin,OUTPUT);
  pinMode(sensorPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(sensorPin);
  tone(speakerPin,value*5,1);
  delay(2);
}
