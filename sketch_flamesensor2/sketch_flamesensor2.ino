void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(12);
  sensorValue= map(sensorValue,0,4095,0,3);
  switch(sensorValue){
    case 0: Serial.print("火はない");
    break;
    case 1: Serial.print("遠くに火");
    break;
    case 2: Serial.print("火に近づいた");
    break;
    case 3: Serial.print("火はすぐそこ");
    
  }
  Serial.println(sensorValue);
  delay(1000);
}
