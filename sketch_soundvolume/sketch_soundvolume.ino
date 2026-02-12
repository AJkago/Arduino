const int micPin=A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int micLevel=analogRead(micPin);

  micLevel=micLevel-512;
  micLevel=abs(micLevel);
  micLevel=map(micLevel,0,512,0,50);

  for(int i =0;i<micLevel;i++){
    Serial.print("#");
    Serial.println("");

    delay(500);
  }
}
