int sensorPin = A0;
int ledPin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(sensorPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue,0,1023,0,255);
  analogWrite(ledPin,sensorValue);
}
