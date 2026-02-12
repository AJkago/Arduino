const int sensorPin=2;
const int buzzerPin=13;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin,OUTPUT);
  pinMode(sensorPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean sensorState = digitalRead(sensorPin);
  digitalWrite(buzzerPin,sensorState);

  delay(10);
}
